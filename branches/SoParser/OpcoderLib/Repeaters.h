#ifndef __SO_REPEATERS_H__
#define __SO_REPEATERS_H__

#include "RuleDecorator.h"

namespace SoParse
{
	class Repeat_ZeroOrOne : public RuleDecorator
	{
		virtual ~Repeat_ZeroOrOne() {}

		virtual char const * getName() const { return "Repeat ?"; }
	};

	class Repeat_ZeroToMany : public RuleDecorator
	{
		virtual ~Repeat_ZeroToMany() {}

		virtual char const * getName() const { return "Repeat *"; }
	};

	class Repeat_OneToMany : public RuleDecorator
	{
		virtual ~Repeat_OneToMany() {}

		virtual char const * getName() const { return "Repeat +"; }
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
		}
		return 0;
	}
}

#endif  // !__SO_REPEATERS_H__