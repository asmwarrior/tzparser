/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/

#ifndef PARSE_DATA_ISTREAM_H__
#define PARSE_DATA_ISTREAM_H__

#include <iostream>

#include "IParseData.h"
#include "AutoPtr.h"

#include "crtdbg.h"

typedef	AutoPtr<std::istream>	APistream;

class ParseDataIStream : public IParseData
{
public:
	ParseDataIStream(std::istream& s) : stream(s) {}
	ParseDataIStream(std::istream* s) : stream(s) {}
	~ParseDataIStream() {}
	virtual char	getChar(void) { char c; stream->get(c); return c; }
	virtual bool	isEndOfFile(void) { return stream->eof(); }
	int	debug() { return (int)this; }

private:
	APistream	stream;
};

#endif	// !PARSE_DATA_ISTREAM_H__
