/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef IPARSEDATA_H_
#define IPARSEDATA_H_

#include "generic/win32_crtdbg.h"

class IParseData
{
public:
	virtual char	getChar(void) = 0;
	virtual bool	isEndOfFile(void) = 0;
	virtual ~IParseData() {};
};

#endif /* IPARSEDATA_H_*/
