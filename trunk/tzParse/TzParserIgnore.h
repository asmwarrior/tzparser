/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSER_IGNORE_H__
#define TZ_PARSER_IGNORE_H__

#include <string>

//#include "TzParseRule.h"

#include "AutoPtr.h"

#include "crtdbg.h"

namespace tzParse
{
	class AParseRule;

	typedef	AutoPtr<AParseRule>		APAParseRule;

	class Ignore
	{
	public:
		Ignore();
		Ignore(const char* str);
		Ignore(const APAParseRule&);
		Ignore(const Ignore& i);
		virtual ~Ignore();

		Ignore&		operator = (const Ignore& i);

		APAParseRule	getRule(void);
		bool			isEmpty(void);

	private:
		void	normalizeRule(void);

		APAParseRule	rule;
	};
}

#endif	// !TZ_PARSER_IGNORE_H__
