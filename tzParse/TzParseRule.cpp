/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#include <string>
#include <iostream>

#include "TzParseRule.h"
#include "TzParser.h"
#include "TzParserUtils.h"

#include "crtdbg.h"

using namespace std;

namespace tzParse
{
	std::string				GetCharUpperString(const char* str)
	{
		std::string	ret(str);
		for (register unsigned int i = 0; i < ret.length(); ++i)
			ret[i] = toupper(ret[i]);
		return ret;
	}

	AParseRule::~AParseRule() {}

	AParseRule&				AParseRule::n(ParseNeed nd, char comaSep /* = 0 */)
	{
		int	min = 1, max = 1;

		if ((nd & PARSE_ZERO_OR_ONE) == PARSE_ZERO_OR_ONE)
			min = 0;
		if ((nd & PARSE_ONE_OR_MORE) == PARSE_ONE_OR_MORE)
			max = 0;

		return n(min, max, comaSep);
	}

	AParseRule&				AParseRule::n(char ndc, char comaSep /* = 0 */)
	{
		switch (ndc)
		{
		case '?':
			return n(PARSE_ZERO_OR_ONE, comaSep);
			break;
		case '+':
			return n(PARSE_ONE_OR_MORE, comaSep);
			break;
		case '*':
			return n(PARSE_ANY, comaSep);
			break;
		}
		return *this;
	}

	AParseRule&		AParseRule::ignore(AParseRule& r)
	{
		_ign = new Ignore(r); return *this;
	}
	
	AParseRule&		AParseRule::ignore(const char* str)
	{
		_ign = new Ignore(str); return *this;
	}

	AParseRule&		AParseRule::noIgnore(void)
	{
		_ign = new Ignore(); return *this;
	}



	/*
	GetChar():				GetChar
	GetChar().only(c):		'c'
	GetChar().in(str):		#GetChar("str")
	GetChar().not(c):		#GetChar(0, 'c')
	GetChar().notIn(str):	#GetChar(0, "str")
	*/
	RULE_IMPLEMENT(GetChar, p)
	{
		char	c;
		bool	ret;

		ret = p.getChar(c);

		if (getParseValue() && !_ignoreBefore)
		{
			char	str[2] = {c, 0};
			setVal(str);
		}

		if (ret && (*_only || *_in || *_but || *_notIn))
		{
			char car;
			if (*_caseIns)
				car = toupper(c);
			else
				car = c;

			if (*_only && ret)
			{
				char only = (*_caseIns ? toupper(*_only) : *_only);
				ret = (car == only);
			}
			if (*_in && ret)
			{
				string in = (*_caseIns ? GetCharUpperString(*_in) : string(*_in));
				ret = (in.find(car) != string::npos);
			}
			if (*_but && ret)
			{
				char but = (*_caseIns ? toupper(*_but) : *_but);
				ret = (but != car);
			}
			if (*_notIn && ret)
			{
				string notIn = (*_caseIns ? GetCharUpperString(*_notIn) : string(*_notIn));
				ret = (notIn.find(car) == string::npos);
			}

			if (!ret)
			{
				p.back();
				return false;
			}
		}

		if (ret && _check)
			p.back();

		return ret;
	}

	/*
	Read().until(s):	#Until("s")
	Read().str(s):		"s"
	*/
	RULE_IMPLEMENT(Read, p)
	{
		if (*_until)
		{
			string	str;
			unsigned int	len = strlen(*_until);

			while (p >> GetChar(str).ignoreBefore(false).r() >> CheckRuleOK())
				if (str.size() >= len && str.substr(str.size() - len, len) == *_until)
					return true;

			return false;
		}

		else if (*_str)
		{
			for (register int i = 0; (*_str)[i]; ++i)
				if (p >> GetChar().only((*_str)[i]).caseInsensitive(*_caseIns).ignoreBefore(false).r() >> CheckRuleFailed())
					return false;

			return true;
		}

		return false;
	}

	RULE_IMPLEMENT(EndOfParse, p)
	{
		p >> GetChar().check().r();
		return p >> CheckRuleFailed();
	}
}
