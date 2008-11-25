#ifndef __SO_REPEATERS_H__
#define __SO_REPEATERS_H__

#include "RuleDecorator.h"

namespace SoParse
{
	class Repeater : public RuleDecorator
	{
	public:
		virtual ~Repeater() {}
	};

	class Repeat_ZeroOrOne : public Repeater
	{
		virtual ~Repeat_ZeroOrOne() {}

		virtual std::string getName() const { return "_Repeat(?)"; }

		virtual OpcodePart *	getOpcodeStart() { return 0; }
		virtual OpcodePart *	getOpcodeEnd() { return 0; }
	};

	class Repeat_ZeroToMany : public Repeater
	{
		virtual ~Repeat_ZeroToMany() {}

		virtual std::string getName() const { return "_Repeat(*)"; }

		virtual OpcodePart *	getOpcodeStart() { return 0; }
		virtual OpcodePart *	getOpcodeEnd() { return 0; }
	};

	class Repeat_OneToMany : public Repeater
	{
		virtual ~Repeat_OneToMany() {}

		virtual std::string getName() const { return "_Repeat(+)"; }

		virtual OpcodePart *	getOpcodeStart() { return 0; }
		virtual OpcodePart *	getOpcodeEnd() { return 0; }
	};

	RuleDecorator * Repeat(char c)
	{
		switch (c)
		{
		case '?':
			return new Repeat_ZeroOrOne;
			break;
		case '*':
			return new Repeat_ZeroToMany;
			break;
		case '+':
			return new Repeat_OneToMany;
			break;
		}
		return 0;
	}
}

#endif  // !__SO_REPEATERS_H__