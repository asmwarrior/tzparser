/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSER_UTILS_H__
#define	TZ_PARSER_UTILS_H__

#include <iostream>

#include "TzParser.h"
#include "crtdbg.h"

namespace tzParse
{
	class Checker
	{
	public:
		virtual bool	check(const Parser& p) const = 0;
	};

	class CheckRuleOK : public Checker
	{
	public:
		bool	check(const Parser& p) const { return !p.ruleFailed(); }
	};

	class CheckRuleFailed : public Checker
	{
	public:
		bool	check(const Parser& p) const { return p.ruleFailed(); }
	};

	inline bool	operator >> (const Parser& p, const Checker& c) { return c.check(p); }
}

#endif	// !TZ_PARSER_UTILS_H__
