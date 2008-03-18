/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

#include "TzTiXMLPrinter.h"

#include "crtdbg.h"

using namespace std;

namespace tzParse
{
	TzTiXMLPrinter::TzTiXMLPrinter(TiXmlDocument* doc)
	{
		strings.push_back("P_HT");
		strings.push_back("P_SP");
		strings.push_back("P_LBLANKS");
		strings.push_back("P_CR");
		strings.push_back("P_LF");
		strings.push_back("P_CRLF");
		strings.push_back("P_NL");
		strings.push_back("P_BLANKS");
		strings.push_back("P_UPALPHA");
		strings.push_back("P_LOALPHA");
		strings.push_back("P_ALPHA");
		strings.push_back("P_NUM");
		strings.push_back("P_DIGIT");
		strings.push_back("P_ALPHANUM");
		strings.push_back("P_CTL");
		strings.push_back("P_TEXT");
		strings.push_back("P_CHAR");
		strings.push_back("P_HEX");
		for (TiXmlElement* node = doc->FirstChildElement("String"); node; node = node->NextSiblingElement("String"))
		{
			if (find(strings.begin(), strings.end(), node->Attribute("Name")) != strings.end())
				throw PrinterException((string("Redefinition of string ") + node->Attribute("Name")).c_str(), atoi(node->Attribute("Line")));

			head << "#define " << node->Attribute("Name") << ' ' << makeLitteral(node->FirstChildElement("Litteral")) << endl;
			strings.push_back(node->Attribute("Name"));
		}

		head << endl;

		for (TiXmlElement* node = doc->FirstChildElement("Rule"); node; node = node->NextSiblingElement("Rule"))
		{
			if (find(strings.begin(), strings.end(), node->Attribute("Name")) != strings.end())
				throw PrinterException((string("Redefinition of string ") + node->Attribute("Name")).c_str(), atoi(node->Attribute("Line")));
			if (find(rules.begin(), rules.end(), node->Attribute("Name")) != rules.end())
				throw PrinterException((string("Redefinition of rule ") + node->Attribute("Name")).c_str(), atoi(node->Attribute("Line")));

			head << "RULE_DECLARE_SIMPLE(" << node->Attribute("Name") << ");" << endl;
			rules.push_back(node->Attribute("Name"));
		}
		rules.push_back("GetChar");
		rules.push_back("Identifier");
		rules.push_back("Integer");
		rules.push_back("Float");
		rules.push_back("QuotedPair");
		rules.push_back("CInChar");
		rules.push_back("CChar");
		rules.push_back("CStr");
		rules.push_back("EndOfParse");

		for (TiXmlElement* node = doc->FirstChildElement("Rule"); node; node = node->NextSiblingElement("Rule"))
		{
			code << endl;
			istringstream	comment(node->Attribute("Value"));
			string line;
			while (getline(comment, line))
				code << "//\t" << line << endl;

			code	<< "RULE_IMPLEMENT(" << node->Attribute("Name") << ", p)" << endl
					<< '{' << endl
					<< "\tp";

			for (TiXmlElement* rc = node->FirstChildElement("RuleCall"); rc; rc = rc->NextSiblingElement("RuleCall"))
				code	<< "\t>>\t" << makeRuleCall(rc) << endl << '\t';

			code	<< "\t;" << endl
					<< "\tRULE_RETURN(p);" << endl
					<< '}' << endl;
		}
	}

	string	TzTiXMLPrinter::makeRuleCall(TiXmlElement* el)
	{
		stringstream	ret;

		string	type(el->Attribute("Type"));
		if (type == "Litteral")
			ret << makeRuleLitteral(el->FirstChildElement("Litteral"));
		else if (type == "Group")
			ret << makeRuleGroup(el->FirstChildElement("Group"));
		else if (type == "TzRule")
			ret << makeTzRule(el->FirstChildElement("TzRule"));

		for (TiXmlElement* md = el->FirstChildElement("TzModif"); md; md = md->NextSiblingElement("TzModif"))
			ret << makeTzModif(md);

		if (TiXmlElement* nd = el->FirstChildElement("Need"))
		{
			ret << ".n(";
			if (nd->Attribute("Simple"))
				ret << '\'' << nd->Attribute("Simple") << '\'';
			else if (nd->Attribute("FixNum"))
				ret << nd->Attribute("FixNum") << ", " << nd->Attribute("FixNum");
			else
			{
				ret	<< (nd->Attribute("Min") ? nd->Attribute("Min") : "0")
					<< ", "
					<< (nd->Attribute("Max") ? nd->Attribute("Max") : "0");
			}
			if (nd->Attribute("Sep"))
				ret << ", '" << nd->Attribute("Sep") << '\'';
			ret << ')';
		}

		for (TiXmlElement* ts = el->FirstChildElement("TreeSave"); ts; ts = ts->NextSiblingElement("TreeSave"))
			if (string("Node") == ts->Attribute("Type"))
			{
				ret << ".saveNode(\"" << ts->Attribute("Name") << '"' << (ts->Attribute("NoValue") ? ", false" : "") << ')';
				if (ts->Attribute("WithLine"))
					ret << ".saveLine()";
			}
			else if (string("Attr") == ts->Attribute("Type"))
				ret << ".saveAttr(\"" << ts->Attribute("Name") << '"' << (ts->Attribute("WithValue") ? (string(", ") + makeLitteral(ts->FirstChildElement("Litteral"))) : "") << ')';

		if (el->FirstChildElement("Check"))
			ret << ".check(" << el->FirstChildElement("Check")->Attribute("Verif") << ")";

		ret << ".r()";

		return ret.str();
	}

	string	TzTiXMLPrinter::makeRuleLitteral(TiXmlElement* el)
	{
		stringstream	ret;

		string			litType = el->Attribute("Type");

		if (litType == "Identifier")
		{
			string value = el->Attribute("Value");

			if (find(rules.begin(), rules.end(), value) != rules.end())
				ret << value << "()";
			else if (find(strings.begin(), strings.end(), value) != strings.end())
				ret << "Read().str(" << value << ")";
			else
				throw PrinterException((value + " : Unknown rule call ").c_str(), atoi(el->Attribute("Line")));
		}
		else if (litType == "CChar")
			ret << "GetChar().only('" << el->Attribute("Value") << "')";
		else if (litType == "CStr")
			ret << "Read().str(\"" << el->Attribute("Value") << "\")";
		else if (litType == "Concat")
			ret << "Read().str(" << makeConcat(el) << ")";

		return ret.str();
	}

	string	TzTiXMLPrinter::makeRuleGroup(TiXmlElement* el)
	{
		stringstream	ret;

		static int indent = 1;

		string type = el->Attribute("Type");

		ret	<<	"( " << ((type == "OR") ? "G_OR" : "G_AND") << endl << '\t';

		++indent;

		for (TiXmlElement* rc = el->FirstChildElement("RuleCall"); rc; rc = rc->NextSiblingElement("RuleCall"))
			ret << setfill('\t') << setw(indent) << "" << ">>\t" << makeRuleCall(rc) << endl << '\t';

		ret << setfill('\t') << setw(indent) << "" << ')';

		--indent;

		return ret.str();
	}


	string	TzTiXMLPrinter::makeLitteral(TiXmlElement* el, string type /* = "" */)
	{
		stringstream	ret;

		if (type == "")
			type = el->Attribute("Type");

		if (type == "CStr" || type == "CChar")
			ret << '"' << el->Attribute("Value") << '"';
		else if (type == "Identifier")
		{
			if (find(strings.begin(), strings.end(), el->Attribute("Value")) == strings.end())
				throw PrinterException((string("Unknown string ") + el->Attribute("Value")).c_str(), atoi(el->Attribute("Line")));
			ret << el->Attribute("Value");
		}
		else if (type == "Concat")
			ret << makeConcat(el);

		return ret.str();
	}

	string	TzTiXMLPrinter::makeConcat(TiXmlElement* el)
	{
		stringstream	ret;

		int	n = 0;
		for (TiXmlElement* node = el->FirstChildElement(); node; node = node->NextSiblingElement())
			++n;

		if (n > 15)
			throw PrinterException("Cannot concat more than 15 elements", atoi(el->Attribute("Line")));

		ret << "P_CONCAT" << n << '(';
		const char*	coma = "";
		for (TiXmlElement* node = el->FirstChildElement(); node; node = node->NextSiblingElement())
		{
			ret << coma << makeLitteral(node, node->Value());
			if (!*coma)
				coma = ", ";
		}
		ret << ')';

		return ret.str();
	}

	std::string	TzTiXMLPrinter::makeTzModif(TiXmlElement* el)
	{
		stringstream	ret;

		string name = el->Attribute("Name");

		if (name == "NoIgnore")
		{
			if (el->FirstChildElement())
				throw PrinterException("NoIgnore does not take any argument", atoi(el->Attribute("Line")));
			ret << ".ignoreBefore(false)";
		}
		else if (name == "Ignore")
		{
			TiXmlElement* lit = el->FirstChildElement();
			if (lit && string("Litteral") != lit->Value())
				throw PrinterException(">Ignore must have a litteral argument", atoi(el->Attribute("Line")));

			ret << ".ignore(";
			if (lit && string("Identifier") == lit->Attribute("Type") && find(rules.begin(), rules.end(), lit->Attribute("Value")) != rules.end())
				ret << lit->Attribute("Value") << "().r()";
			else if (lit)
				ret << makeLitteral(lit);
			ret << ')';

			if (lit && lit->NextSiblingElement())
				throw PrinterException(">Ignore just takes one argument", atoi(el->Attribute("Line")));
		}
		else if (name == "Force")
		{
			TiXmlElement* lit = el->FirstChildElement();
			if (!lit || string("Litteral") != lit->Value())
				throw PrinterException(">Force must have a litteral argument", atoi(el->Attribute("Line")));

			ret << ".force(" << makeLitteral(lit) << ')';

			if (lit->NextSiblingElement())
				throw PrinterException(">Force just takes one argument", atoi(el->Attribute("Line")));

		}

		if (ret.str() == "")
			throw PrinterException((name + ": Unknown TzModif").c_str(), atoi(el->Attribute("Line")));

		return ret.str();
	}

	std::string	TzTiXMLPrinter::makeTzRule(TiXmlElement* el)
	{
		stringstream	ret;

		string	name = el->Attribute("Name");
		if (name == "GetChar")
		{
			ret << "GetChar()";

			TiXmlElement* arg = el->FirstChildElement();
			if (arg && string("Bool") == arg->Value())
			{
				ret << ".caseInsensitive(" << arg->Attribute("Value") << ')';

				if (!arg->NextSiblingElement())
					throw PrinterException("Attempting litteral argument in #GetChar", atoi(el->Attribute("Line")));

				arg = arg->NextSiblingElement();
			}			

			if (arg)
			{
				if (string("Litteral") != arg->Value() && string("Null") != arg->Value())
					throw PrinterException("Attempting litteral or null argument in #GetChar", atoi(el->Attribute("Line")));
				if (string("Litteral") == arg->Value())
				{
					if (string("CChar") == arg->Attribute("Type"))
						ret << ".only('" << arg->Attribute("Value") << "')";
					else
						ret << ".in(" << makeLitteral(arg) << ')';
				}

				if (string("Null") == arg->Value() && !arg->NextSiblingElement())
					throw PrinterException("Attempting litteral argument in #GetChar", atoi(el->Attribute("Line")));

				arg = arg->NextSiblingElement();
			}

			if (arg)
			{
				if (string("Litteral") != arg->Value())
					throw PrinterException("Attempting litteral argument in #GetChar", atoi(el->Attribute("Line")));
				if (string("CChar") == arg->Attribute("Type"))
					ret << ".but('" << arg->Attribute("Value") << "')";
				else
					ret << ".notIn(" << makeLitteral(arg) << ')';

				if (arg->NextSiblingElement())
					throw PrinterException("To much Argument in #GetChar", atoi(el->Attribute("Line")));

			}
		}

		else if (name == "ReadUntil")
		{
			TiXmlElement* arg = el->FirstChildElement();
			if (!arg || string("Litteral") != arg->Value() || arg->NextSiblingElement())
				throw PrinterException("#ReadUntil must take only one litteral argument", atoi(el->Attribute("Line")));

			ret << "Read().until(" << makeLitteral(arg) << ')';
		}

		else if (name == "Identifier")
		{
			ret << "Identifier()";

			TiXmlElement* arg = el->FirstChildElement();
			if (arg)
			{
				if (string("Bool") != arg->Value() || arg->NextSiblingElement())
					throw PrinterException("#Identifier must take only one bool argument", atoi(el->Attribute("Line")));
				ret << ".checkFirstChar(" << arg->Attribute("Value") << ')';
			}
		}

		else if (name == "Integer")
		{
			ret << "Integer()";

			TiXmlElement* arg = el->FirstChildElement();
			if (arg)
			{
				if (string("Bool") != arg->Value() || arg->NextSiblingElement())
					throw PrinterException("#Integer must take only one bool argument", atoi(el->Attribute("Line")));
				if (string("false") == arg->Attribute("Value"))
					ret << ".forceNegative()";
				else
					ret << ".forcePositive()";
			}
		}

		else if (name == "Float")
		{
			ret << "Float()";

			TiXmlElement* arg = el->FirstChildElement();
			if (arg && string("Bool") == arg->Value())
			{
				if (string("false") == arg->Attribute("Value"))
					ret << ".forceNegative()";
				else
					ret << ".forcePositive()";
				arg = arg->NextSiblingElement();
			}

			if (arg)
			{
				if (string("Litteral") != arg->Value() || string("CChar") != arg->Attribute("Type"))
					throw PrinterException("Attempting CChar argument in #Float", atoi(el->Attribute("Line")));
				ret << ".coma('" << arg->Attribute("Value") << "')";

				if (arg->NextSiblingElement())
					throw PrinterException("To much Argument in #Float", atoi(el->Attribute("Line")));
			}
		}

		return ret.str();
	}

}
