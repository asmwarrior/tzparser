/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSE_EXCEPTION_H__
#define	TZ_PARSE_EXCEPTION_H__

#include <string>
#include <sstream>
#include <exception>

#include "generic/win32_crtdbg.h"


namespace tzParse
{
	class ParseException : public std::exception
	{
	public:
		ParseException(const char* e, int l = -1);
		ParseException(const ParseException& e) : line(e.line), err(e.err), mess(e.mess), std::exception() {}
		virtual ~ParseException() throw() {}
		const char*				getError(void) const { return err.c_str();  }
		int						getLine(void) const  { return line; }
		virtual const char*		what(void) const throw() { return mess.c_str(); }

	private:
		const int		line;
		std::string		err;
		std::string		mess;
	};

	inline ParseException::ParseException(const char* e, int l /* = -1 */) : err(e), line(l)//, std::exception("Parse Error")
	{
		std::ostringstream	tmp;

		tmp << "Parse Error :\n";

		if (err != "")
			tmp << ' ' << err;

		if (line > 0)
			tmp <<" on line " << line;

		tmp << std::endl;

		mess = tmp.str();
	}
}

#endif	// !TZ_PARSE_EXCEPTION_H__
