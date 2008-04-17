/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_TIXML_PRINTER_H__
#define	TZ_TIXML_PRINTER_H__

#include <string>
#include <sstream>
#include <list>
#include <map>

#include "tinyxml/tinyxml.h"

typedef	std::list<std::string>				stringList;
//typedef	std::map<std::string, std::string>	stringMap;

namespace tzParse
{
	class TzTiXMLPrinter
	{
	public:
		TzTiXMLPrinter(TiXmlDocument* doc);

		std::string	getCode() { return code.str(); }
		std::string	getHead() { return head.str(); }

	private:
		std::string	makeRuleCall(TiXmlElement* el);
		std::string	makeRuleLitteral(TiXmlElement* el);
		std::string	makeRuleGroup(TiXmlElement* el);
		std::string	makeLitteral(TiXmlElement* el, std::string type = "");
		std::string	makeConcat(TiXmlElement* el);
		std::string	makeTzModif(TiXmlElement* el);
		std::string	makeTzRule(TiXmlElement* el);

//		void		makeInstruction(TiXmlElement* el);

		stringList	rules;
		stringList	strings;

		std::stringstream	head;
		std::stringstream	code;
	};




	class PrinterException : public std::exception
	{
	public:
		PrinterException(const char* e, int l = -1);
		PrinterException(const PrinterException& e) : line(e.line), err(e.err), mess(e.mess) {}
		virtual ~PrinterException() throw() {}
		const char*				getError(void) const { return err.c_str();  }
		int						getLine(void) const  { return line; }
		virtual const char*		what(void) const throw() { return mess.c_str(); }

	private:
		const int		line;
		std::string		err;
		std::string		mess;
	};

	inline PrinterException::PrinterException(const char* e, int l /* = -1 */) : err(e), line(l)
	{
		std::ostringstream	tmp;

		tmp << "Printer Error :\n";

		if (err != "")
			tmp << ' ' << err;

		if (line > 0)
			tmp <<" on line " << line;

		tmp << std::endl;

		mess = tmp.str();
	}
}

#endif	// !TZ_TIXML_PRINTER_H__
