/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSER_H__
#define	TZ_PARSER_H__

#include <sstream>
#include <string>
#include <stack>
#include <list>

#include <iostream>

#include "IParseData.h"
#include "ParseDataIStream.h"
#include "AutoPtr.h"
#include "TzParserIgnore.h"
#include "TzParseException.h"
#include "TzParseAST.h"
#include "TzParseStream.h"
#include "TzParseGroup.h"

#include "crtdbg.h"

namespace tzParse
{
	class AParseRule;
	class GetChar;

	typedef	AutoPtr<IParseData>			APIParseData;
	typedef	std::stack<APIParseData>	APIParseDataStack;

	struct ParserContext 
	{
		ParserContext() : line(0), pos(0){}
		ParserContext(const ParserContext& ctx) : line(ctx.line), pos(ctx.pos) {}
		virtual ~ParserContext() {}

		unsigned int	line;
		unsigned int	pos;
	};

	class Parser
	{
	public:
		Parser() : ruleFail(false), line(1), _trace(-1), _noTrace(0), inIgnore(0), stopIgnore(false), precCtx(0), xmldoc(0), curElement(0), _idebug(0) {}
		virtual ~Parser() {}

 		Parser&			operator << (APIParseData i) { ipdStack.push(i); return *this; }
		Parser&			operator << (IParseData& i) { ipdStack.push(i); return *this; }
 		Parser&			operator << (std::istream& i) { ipdStack.push(new ParseDataIStream(i)); return *this; }
		Parser&			operator << (std::string i) { ipdStack.push(new ParseDataIStream(new std::istringstream(i))); return *this; }
 		Parser&			operator << (char& c) { str.putback(c); return *this; }

		Parser&			operator >> (AParseRule&);
		Parser&			operator >> (ParseGroup& g) { return *this >> g.r(); }


		ParserContext	getContext(void);
		void			setContext(const ParserContext&);

		std::string		getParsed(void);
		std::string		getParsedFrom(std::streampos);
		std::string		getParsedFrom(const ParserContext&);

		bool			getChar(char& c);
		void			back(void);

		bool			ruleFailed(void) const { return ruleFail; }
		void			reinitFailBit(void) { ruleFail = false; }

		void			trace(void) { if (_trace < 0) _trace = 0; }

		void			setXMLDoc(IParseASTDocument* doc) { xmldoc = doc; }

	private:
		bool				ruleFail;
		int					line;

		TzParseStream		str;
		APIParseDataStack	ipdStack;

		Ignore				ignore;
		bool				stopIgnore;

		int					_trace;
		int					_noTrace;
		int					inIgnore;

		ParserContext*		precCtx;

		IParseASTDocument*	xmldoc;

		IParseASTElement*	curElement;

		int					_idebug;
	};

}

#endif	// !TZ_PARSER_H__
