#ifndef __SO_READCHAR_H__
#define __SO_READCHAR_H__

#include "Rule.h"

namespace SoParse
{
	class ReadAChar : public IRule
	{
	public:
		ReadAChar(char c) : _c(c) {}

		virtual char const * getName() const { return "GetChar"; }

	private:
		const char _c;
	};

	inline APIRule ReadChar(char c)
	{
		return APIRule(new ReadAChar(c));
	};

	class ReadCharRange : public IRule
	{
	public:
		ReadCharRange(char s, char e) : _s(s), _e(e) {}

		virtual char const * getName() const { return "GetChar"; }

	private:
		const char _s;
		const char _e;
	};

	inline APIRule ReadChar(char s, char e)
	{
		return APIRule(new ReadCharRange(s, e));
	};
}

#endif  // !__SO_READCHAR_H__
