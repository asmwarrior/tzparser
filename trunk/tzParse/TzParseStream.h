/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSE_STREAM_H__
#define	TZ_PARSE_STREAM_H__

#include "crtdbg.h"

namespace tzParse
{
	class TzParseStream
	{
	public:
		TzParseStream() : pos(0) {}
		virtual ~TzParseStream() {}

		std::string	getStr(void) { return str; }

		void	put(char c)
		{
			str += c;
			if (pos == str.length() - 1)
				++pos;
		}
 		void	putback(char c) { str += c; }

		bool	avail(void) { return (pos < str.length()); }
		char	get(void) { return str[pos++]; }
		char	peek(void) { return str[pos]; }

		void	back(void) { if (pos > 0) --pos; }

		unsigned int	getPos(void) { return pos; }
		void			setPos(unsigned int p) { pos = p; }

		std::string		emptyToRead(void)
		{
			std::string ret = str.substr(pos);
			str = str.substr(0, pos);
			return ret;
		}

	private:
		std::string		str;
		unsigned int	pos;
	};
}

#endif	// !TZ_PARSE_STREAM_H__
