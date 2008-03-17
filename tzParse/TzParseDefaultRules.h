/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSE_DEFAULT_RULES_H__
#define	TZ_PARSE_DEFAULT_RULES_H__

#include "TzParseRule.h"

#include "crtdbg.h"

namespace tzParse
{
	RULE_DECLARE_HEAD(Identifier)
	{
		RULE_HEAD(Identifier);
		RULE_SIMPLE_CLONE(Identifier);

		RULE_ARG(_cfc, bool, true);
		RULE_METHARG(Identifier, checkFirstChar, _cfc, bool);
	};

	RULE_DECLARE_HEAD(Integer)
	{
		RULE_HEAD(Integer);
		RULE_SIMPLE_CLONE(Integer);

		RULE_ARG(_fp, bool, false);
		RULE_METHARG_DEF(Integer, forcePositive, _fp, bool, true);
		RULE_ARG(_fn, bool, false);
		RULE_METHARG_DEF(Integer, forceNegative, _fn, bool, true);
	};

	RULE_DECLARE_HEAD(Float)
	{
		RULE_HEAD(Float);
		RULE_SIMPLE_CLONE(Float);

		RULE_STDARG(Float, coma, char, '.');

		RULE_ARG(_fp, bool, false);
		RULE_METHARG_DEF(Float, forcePositive, _fp, bool, true);
		RULE_ARG(_fn, bool, false);
		RULE_METHARG_DEF(Float, forceNegative, _fn, bool, true);
	};

	RULE_DECLARE_HEAD(QuotedPair)
	{
		RULE_HEAD(QuotedPair);
		RULE_SIMPLE_CLONE(QuotedPair);
		RULE_NO_TRACE();
	};

	RULE_DECLARE_HEAD(CInChar)
	{
		RULE_HEAD(CInChar);
		RULE_SIMPLE_CLONE(CInChar);
		RULE_NO_TRACE();

		RULE_STDARGNULL(CInChar, but, char);
	};

	RULE_DECLARE_SIMPLE(CChar);
	RULE_DECLARE_SIMPLE(CStr);
}

#endif	// !TZ_PARSE_DEFAULT_RULES_H__
