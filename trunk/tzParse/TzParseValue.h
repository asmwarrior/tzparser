/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_TYPE_TO_PARSE_H__
#define	TZ_TYPE_TO_PARSE_H__

#include <string>
#include <iostream>

#include "generic/AutoPtr.h"
#include "TzParseNeed.h"

#include "generic/win32_crtdbg.h"

#define	PARSETYPEDECLARE(typeName, type)	class typeName : public ParseType<type>						\
											{															\
											public:														\
												typeName(type& v) : ParseType<type>(v) {}				\
												virtual type	convert(const std::string&) const;		\
											}

#define	PARSEVALUECONSTRUCT(typeName, type)	ParseValue(type& v) : parseType(new typeName(v)) {}

#define	PARSETYPEIMPLEMENT(typeName, type, Pchar)	type typeName::convert(const std::string& Pchar) const

namespace tzParse
{
	class	IParseType
	{
	public:
		virtual void		setVal(const std::string& str) = 0;
	};

	template<typename T>
	class ParseType : public IParseType
	{
	public:
		ParseType(T& v) : val(&v) {}
		void			saveVal(T v) { if (val) *val = v; }
		T*				getValPtr(void) const { return val; }
		virtual T		convert(const std::string&) const = 0;
		virtual void	setVal(const std::string& str) { saveVal(convert(str)); }

	protected:
		T*	val;
	};

	PARSETYPEDECLARE(ParseChar, char);
	PARSETYPEDECLARE(ParseInt, int);
	PARSETYPEDECLARE(ParseFloat, float);
	PARSETYPEDECLARE(ParseDouble, double);
	PARSETYPEDECLARE(ParseString, std::string);

	typedef AutoPtr<IParseType>	APIParseType;

	class ParseValue : public IParseType
	{
	public:
		ParseValue(IParseType& i) : parseType(i) {}
		ParseValue(const ParseValue& pv) : parseType(pv.parseType), IParseType() {}
		virtual void	setVal(const std::string& str) { parseType->setVal(str); }
		virtual ~ParseValue() {}

		PARSEVALUECONSTRUCT(ParseChar, char)
		PARSEVALUECONSTRUCT(ParseInt, int)
		PARSEVALUECONSTRUCT(ParseFloat, float)
		PARSEVALUECONSTRUCT(ParseDouble, double)
		PARSEVALUECONSTRUCT(ParseString, std::string)

	private:
		APIParseType		parseType;
	};
}

#endif	// !TZ_TYPE_TO_PARSE_H__
