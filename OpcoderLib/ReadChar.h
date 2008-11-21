#ifndef __SO_READCHAR_H__
#define __SO_READCHAR_H__

#include "AtomicRule.h"

namespace SoParse
{
	class ReadAnyChar : public AtomicRule
	{
	public:
		virtual ~ReadAnyChar() {}
		ReadAnyChar() {}

		virtual std::string getName() const { return "GetChar)"; }

		virtual std::string	getOpcodeStart() { return std::string("\x20\x00\x00", 3); }
		virtual std::string	getOpcodeEnd() { return ""; }
	};

	inline APIRule ReadChar()
	{
		return APIRule(new ReadAnyChar);
	};

	class ReadAChar : public AtomicRule
	{
	public:
		virtual ~ReadAChar() {}
		ReadAChar(char c) : _c(c) {}

		virtual std::string getName() const { return std::string("GetChar(") + _c + ')'; }

		virtual std::string	getOpcodeStart() { return std::string("\x21", 1).append(_c, 1).append("\x00", 1); }
		virtual std::string	getOpcodeEnd() { return ""; }

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

		virtual std::string	getOpcodeStart() { return std::string("\x22", 1).append(_s, 1).append(_e, 1); }
		virtual std::string	getOpcodeEnd() { return ""; }

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
