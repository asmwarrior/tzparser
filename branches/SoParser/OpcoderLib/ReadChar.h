#ifndef __SO_READCHAR_H__
#define __SO_READCHAR_H__

#include "AtomicRule.h"

namespace SoParse
{
	class ReadAChar : public AtomicRule
	{
	public:
		virtual ~ReadAChar() {}
		ReadAChar(char c) : _c(c) {}

		virtual std::string getName() const { return std::string("GetChar(") + _c + ')'; }

	private:
		const char _c;
	};

	inline APIRule ReadChar(char c)
	{
		return APIRule(new ReadAChar(c));
	};

	class ReadCharRange : public AtomicRule
	{
	public:
		virtual ~ReadCharRange() {}

		ReadCharRange(char s, char e) : _s(s), _e(e) {}

		virtual std::string getName() const { return std::string("GetChar(") + _s + ", " + _e + ")"; }

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
