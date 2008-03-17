/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSE_NEED_H__
#define	TZ_PARSE_NEED_H__

#include "crtdbg.h"

namespace tzParse
{
	enum ParseNeed
	{
		PARSE_ONE			= 0x0,	// 00
		PARSE_ZERO_OR_ONE	= 0x1,	// 01
		PARSE_ONE_OR_MORE	= 0x2,	// 10

		PARSE_ANY = PARSE_ZERO_OR_ONE | PARSE_ONE_OR_MORE,	//	= 0x11

		PARSE_ZOO = PARSE_ZERO_OR_ONE,
		PARSE_OOM = PARSE_ONE_OR_MORE
	};
}

#endif	// !TZ_PARSE_NEED_H__
