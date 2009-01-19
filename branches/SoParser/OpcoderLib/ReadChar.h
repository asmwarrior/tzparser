#ifndef __SO_READCHAR_H__
#define __SO_READCHAR_H__

#include "AtomicRule.h"
#include "Opcodes.h"

#include <string>

namespace SoParse
{
	class ReadAnyChar : public AtomicRule
	{
	public:
		virtual ~ReadAnyChar() {}
		ReadAnyChar() {}

		virtual std::string getName() const { return "ReadChar()"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return new OpcodePart(READ_CHAR); }
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

		virtual std::string getName() const { return std::string("ReadChar(") + _c + ')'; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return new OpcodePart(READ_A_CHAR, _c, 0); }

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

		virtual std::string getName() const { return std::string("ReadChar(") + _s + ", " + _e + ")"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return new OpcodePart(READ_CHAR_RANGE, _s, _e); }

	private:
		const char _s;
		const char _e;
	};

	inline APIRule ReadChar(char s, char e)
	{
		return APIRule(new ReadCharRange(s, e));
	};

	class ReadCharIn : public AtomicRule
	{
	public:
		virtual ~ReadCharIn() {}

		ReadCharIn(const std::string & chars) : _chars(chars) {}

		virtual std::string getName() const { return std::string("ReadChar(\"") + _chars + "\")"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return (new OpcodePart(READ_CHAR_IN))->addRefArgHere(_chars); }

	private:
		std::string	_chars;
	};

	inline APIRule ReadChar(std::string chars)
	{
		return APIRule(new ReadCharIn(chars));
	};
}

#endif  // !__SO_READCHAR_H__
