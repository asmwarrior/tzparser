/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#include <iostream>
#include <iomanip>
#include <cstring>

#include "TzParser.h"
#include "TzParseRule.h"
#include "TzParserUtils.h"

#include "TzParseTempAST.h"

#include "generic/win32_crtdbg.h"

#define	TRACE_BOOL	(_trace >= 0 && inIgnore == 0 && r.traceRule() && _noTrace == 0)

using namespace std;

namespace tzParse
{
	Parser&		Parser::operator >> (AParseRule& r)
	{
		// On n'execute pas la regle si on est en etat d'echec
		if (ruleFail)
			return *this;

		// On trace l'entree
		if (_trace >= 0 && inIgnore == 0)
		{
			if (r.traceRule() && _noTrace == 0)
				cout << setw(_trace++ * 2) << setfill(' ') << "" << "IN : " << r.getRuleName() << "(l." << line << ')' << " [" << this->str.getPos() << "] " << endl;
			else
				++_noTrace;
		}

		// On set l'ignore
		Ignore	*ctxIgnore = 0;
		if (r.getIgnore().getPtr())
		{
			ctxIgnore = new Ignore(ignore);
			ignore = *(r.getIgnore());
			stopIgnore = false;
		}
		if (!r.getIgnoreBefore())
			stopIgnore = true;

		// Eventuelle premiere sauvegarde de contexte (en cas d'echec)
		ParserContext*	ctx1 = 0;
		bool			ctx1Prec = false;
		if (!r.simpleChar() || TRACE_BOOL)
		{
			if (precCtx && str.getPos() == precCtx->pos)
			{
				ctx1 = precCtx;
				ctx1Prec = true;
			}
			else
			{
				ctx1 = new ParserContext(getContext());
				precCtx = ctx1;
			}
		}

		// On ignore
		bool	ignoreDone = false;
		if (r.getIgnoreBefore() && !ignore.isEmpty() && !stopIgnore)
		{
			if (_trace >= 0)
				cout << setw(_trace * 2) << setfill(' ') << "" << "[IGNORE]" << endl;

			Ignore tmpIgn = ignore;
			ignore = Ignore();

			++inIgnore;
 			ignoreDone = *this >> *(tmpIgn.getRule()) >> CheckRuleOK();
			--inIgnore;

			ignore = tmpIgn;
			ruleFail = false;
			stopIgnore = true;
		}

		// Eventuelle seconde sauvegarde de contexte (pour la sauvegarde)
		ParserContext*	ctx2 = 0;
		if (r.getSNode() || r.getSAttr() || (r.getParseValue().getPtr() && !r.simpleChar()) || TRACE_BOOL)
		{
			if (ignoreDone || !ctx1)
				ctx2 = new ParserContext(getContext());
			else
				ctx2 = ctx1;
		}

		// On cree un node si necessaire
		IParseASTElement*	oldElement = curElement;
		TzParseASTTmpEl*	tmpElement = 0;
		if (r.getSNode() && xmldoc)
			curElement = xmldoc->createElement(r.getSNode());
		else if (xmldoc)
		{
			tmpElement = new TzParseASTTmpEl();
			curElement = tmpElement;
		}

		// Execution
		ParseException* error = 0;
		try
		{
			ruleFail = !r.execute(*this);
		}
		catch (ParseException& e)
		{
			error = new ParseException(e);
			ruleFail = true;
		}

		// On sauve ce qui vient d'etre parse s'il y a eu sauvegarde de contexte
		if (!ruleFail && ctx2)
		{
			if (r.getSaveValue().empty())
				r.setVal(getParsedFrom(*ctx2));
			else
				r.setVal(r.getSaveValue());
		}

		// On met dans l'arbre si c'est demande
		if (xmldoc && (r.getSAttr() || tmpElement || r.getSNode()))
		{
			std::string toSave;
			if (!ruleFail && ( (r.getSAttr() && !r.getSAttrVal()) || (r.getSNode() && r.getSNodeWithVal()) ))
			{
				if (r.getSaveValue().empty() && ctx2)
					toSave = getParsedFrom(*ctx2);
				else
					toSave = r.getSaveValue();
			}

			int			lineSave = line;
			if (ctx2)
				lineSave = ctx2->line;

			if (r.getSAttr() && !ruleFail && oldElement)
			{
				if (r.getSAttrVal())
					oldElement->setAttribute(r.getSAttr(), r.getSAttrVal());
				else
					oldElement->setAttribute(r.getSAttr(), toSave);
			}
			if (tmpElement)
			{
				if (!ruleFail)
				{
					if (oldElement)
						tmpElement->mergeAll(oldElement);
					else
						tmpElement->merge(xmldoc);
				}
				delete tmpElement;
			}
			else if (r.getSNode() && curElement)
			{
				if (!ruleFail)
				{
					if (r.getSNodeWithVal())
						curElement->setAttribute("Value", toSave);
					if (r.getSaveLine())
					{
						stringstream l;
						l << lineSave;
						curElement->setAttribute("Line", l.str());
					}
					if (oldElement)
						oldElement->addChild(curElement);
					else
						xmldoc->addChild(curElement);
				}
				else
					delete curElement;
			}
		}
		curElement = oldElement;

		// On trace la sortie
		if (_trace >= 0 && inIgnore == 0)
		{
			if (_noTrace == 0)
			{
				cout << setw(--_trace * 2) << setfill(' ') << "" << "OUT : " << r.getRuleName() << "(l." << line << ')' << " : " << boolalpha << !ruleFail;
				if (!ruleFail && ctx2)
					cout << " : [" << getParsedFrom(*ctx2) << ']';
				cout << endl;
			}
			else
				--_noTrace;
		}

		// On delete le contexte de sauvegarde
		if (ctx2 && ctx2 != ctx1)
			delete ctx2;

		// Execution multiple s'il y a lieu
		if (!ruleFail && r.getMax() != 1)
		{
			AParseRule*	nr = r.clone();
			nr->n(PARSE_ONE);
			nr->removeIgnore();
			nr->force();
			nr->noCheck();
 
			register unsigned int i;
			for (i = 1; !ruleFail && ( r.getMax() == 0 || i < r.getMax() ); ++i)
			{
				try
				{
					if (r.getComaSep())
						*this >> GetChar().only(r.getComaSep()) >> *nr;
					else
						*this >> *nr;
				}
				catch (ParseException& e)
				{
					error = new ParseException(e);
					ruleFail = true;
				}
			}
 			delete nr;

			if (--i >= r.getMin())
				ruleFail = false;
		}

		// On verifie si checkType renverse le resultat
		if (r.getCheck() && r.getCheckType() == false)
		{
			ruleFail = !ruleFail;
		}

		// Eventuelle restauration de contexte
		if ((ruleFail || r.getCheck()) && ctx1)
			setContext(*ctx1);
		if (ctx1 && !ctx1Prec)
		{
			delete ctx1;
			precCtx = 0;
		}

		// Si l'execution etait facultative, on reset rulefail a false
		if (r.getMin() == 0)
			ruleFail = false;

		// Eventuelle restauration d'ignore
		if (ctxIgnore)
		{
			ignore = *ctxIgnore;
			delete ctxIgnore;
		}

		// Si la regle a reussie, on remet stopIgnore a false
		if (!ruleFail)
			stopIgnore = false;

		if (!ruleFail)
			precCtx = 0;

		// Si la regle a echoue et qu'elle etait obligatoire, on lance une exception
		if (r.getForce() && ruleFail && !error)
			error = new ParseException(r.getForce(), line);

		// En cas d'erreur, on fait suivre
		if (error)
		{
			ParseException	err(*error);
			delete error;
			throw err;
		}

		return *this;
	}

	ParserContext		Parser::getContext(void)
	{
		ParserContext	ret;

		ret.pos = str.getPos();

		ret.line = line;

		return ret;
	}

	void			Parser::setContext(const ParserContext& c)
	{
		line = c.line;
		str.setPos(c.pos);
	}

	string			Parser::getParsed(void)
	{
		return str.getStr().substr(0, str.getPos());
	}

	std::string		Parser::getParsedFrom(std::streampos pos)
	{
		if ((int)pos == -1)
			pos = 0;
//		cout << "UN [" << str.getStr() << "] " << pos << ", " << (str.getPos() - pos) << endl;
		string ret = str.getStr().substr(pos, str.getPos() - pos);
//		cout << "DEUX" << endl;
		return ret;
	}

	std::string		Parser::getParsedFrom(const ParserContext& c)
	{
		return getParsedFrom(c.pos);
	}


	bool		Parser::getChar(char &c)
	{
		// On verifie si il y a quelque chose a lire dans la string
		if (str.avail())
		{
			c = str.get();

			// On incremente la ligne courante si on tombe sur un \n
			if (c == '\n')
				++line;

			return true;
		}

		// On verifie si la stack est pas deja vide
		if (ipdStack.empty())
		{
			c = 0;
			return false;
		}

		// On recupere le premier IParseData
		IParseData*	parseData = ipdStack.top();

		// On verifie si c'est la fin du IParseData actuel. Si c'est le cas, on pop et on verifie que la stack est pas rendue vide.
		if (parseData->isEndOfFile())
		{
			ipdStack.pop();
			if (ipdStack.empty())
			{
				c = 0;
				return false;
			}
			parseData = ipdStack.top();
		}

		// On recupere le premier caractere du premier iStream de la stack
		c = parseData->getChar();

		// On verifie que ce n'etait pas le caractere de fin de la stream, et donc qu'elle n'est pas vide. Si c'est le cas, on recommence le processus
		if (parseData->isEndOfFile())
			return getChar(c);

		// On insere le caractere dans la stringstream
		str.put(c);

		// On incremente la ligne courante si on tombe sur un \n
		if (c == '\n')
			++line;
		return true;
	}

	void			Parser::back(void)
	{
		str.back();
		if (str.peek() == '\n')
			--line;
	}
}
