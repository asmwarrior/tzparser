/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#include <iostream>

#include "TzParseValue.h"

#include "crtdbg.h"

using namespace std;

namespace tzParse
{
	PARSETYPEIMPLEMENT(ParseChar, char, str)
	{
		return str[0];
	}

	PARSETYPEIMPLEMENT(ParseInt, int, str)
	{
		return atoi(str.c_str());
	}

	PARSETYPEIMPLEMENT(ParseFloat, float, str)
	{
		return (float)atof(str.c_str());
	}

	PARSETYPEIMPLEMENT(ParseDouble, double, str)
	{
		return atof(str.c_str());
	}

	PARSETYPEIMPLEMENT(ParseString, std::string, str)
	{
		return *val + str;
	}
}
