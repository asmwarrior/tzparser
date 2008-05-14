/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#include <iostream>

#include "TzParseDefaultRules.h"
#include "TzParseGroup.h"
#include "TzParserUtils.h"
#include "TzParseString.h"

#include "generic/win32_crtdbg.h"

using namespace std;

namespace tzParse
{
	/*
		#GetChar(P_ALPHA) >NoIgnore #GetChar(P_ALPHANUM)*
	*/
	RULE_IMPLEMENT(Identifier, p)
	{
		char c;
		p	>>	GetChar(c).in((*_cfc) ? P_CONCAT2("_", P_ALPHA) : P_CONCAT2("_", P_ALPHANUM)).r()
			>>	GetChar().in(P_CONCAT2("_", P_ALPHANUM)).ignoreBefore(false).n(PARSE_ANY).r()
			;
		RULE_RETURN(p);
	}

	/*
		[
			'-' >NoIgnore #GetChar(P_NUM)+
		|
			#GetChar(P_NUM) >NoIgnore #GetChar(P_NUM)*
		]
	*/
	RULE_IMPLEMENT(Integer, p)
	{
		if (!*_fp && !*_fn)
		{
			p	>>	( G_OR
					>>	( G_AND
						>>	GetChar().only('-').r()
						>>	GetChar().in(P_NUM).ignoreBefore(false).n(PARSE_ONE_OR_MORE).r()
						).r()
					>>	( G_AND
						>>	GetChar().in(P_NUM).r()
						>>	GetChar().in(P_NUM).ignoreBefore(false).n(PARSE_ANY).r()
						).r()
					).r()
				;
		}
		else if (*_fp)
		{
			p	>>	GetChar().in(P_NUM).r()
				>>	GetChar().in(P_NUM).ignoreBefore(false).n(PARSE_ANY).r()
				;
		}
		else if (*_fn)
		{
			p	>>	( G_AND
					>>	GetChar().only('-').r()
					>>	GetChar().in(P_NUM).ignoreBefore(false).n(PARSE_ONE_OR_MORE).r()
					).r()
				;
		}

		RULE_RETURN(p);
	}

	/*
		[
			Integer [ >NoIgnore '.' >NoIgnore #Integer(+) ]?
		|
			'-'? >NoIgnore '.' >NoIgnore #Integer(+)
		]
	*/
	RULE_IMPLEMENT(Float, p)
	{
		p	>>	Integer().forcePositive(*_fp).forceNegative(*_fn).r()
			>>	( G_AND
					>> GetChar().only(*_coma).ignoreBefore(false).r()
					>> Integer().forcePositive().ignoreBefore(false).r()
				).n(PARSE_ZERO_OR_ONE).r()
			;
		if (p >> CheckRuleFailed())
		{
			if (*_fn)
				p	>>	GetChar().only('-').r();
			p	>> GetChar().only(*_coma).ignoreBefore(false).r()
				>> Integer().forcePositive().ignoreBefore(false).r()
				;
		}

		RULE_RETURN(p);
	}

	/*
		'\' GetChar
	*/
	RULE_IMPLEMENT(QuotedPair, p)
	{
		p	>> GetChar().only('\\').r()
			>> GetChar().ignoreBefore(false).r()
			;
		RULE_RETURN(p);
	}

	/*
		[ QuotedPair | GetChar ]
	*/
	RULE_IMPLEMENT(CInChar, p)
	{
		std::string	str;
		p	>>	( G_OR
				>>	QuotedPair(str).r()
				>>	GetChar(str).but(*_but).r()
				).r()
			;

		RULE_RETURN(p);
	}

	/*
		'\'' >NoIgnore CInChar >NoIgnore '\''
	*/
	RULE_IMPLEMENT(CChar, p)
	{
		string	str;

		p	>> GetChar().only('\'').r()
			>> CInChar(str).ignoreBefore(false).r()
			>> GetChar().only('\'').ignoreBefore(false).r()
			;

		RULE_VAL_SAVE(str);

		RULE_RETURN(p);
	}

	/*
		'"' >NoIgnore CInChar* >NoIgnore '"'
	*/
	RULE_IMPLEMENT(CStr, p)
	{
		string	str;

		p	>> GetChar().only('"').r()
			>> CInChar(str).but('"').ignoreBefore(false).n(PARSE_ANY).r()
			>> GetChar().only('"').ignoreBefore(false).r()
			;

		RULE_VAL_SAVE(str);

		RULE_RETURN(p);
	}
}
