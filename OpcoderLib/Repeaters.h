#ifndef __SO_REPEATERS_H__
#define __SO_REPEATERS_H__

#include "RuleDecorator.h"

namespace SoParse
{
	class Repeat_ZeroOrOne : public RuleDecorator
	{
		virtual ~Repeat_ZeroOrOne() {}
	};

	class Repeat_ZeroToMany : public RuleDecorator
	{
		virtual ~Repeat_ZeroToMany() {}
	};

	class Repeat_OneToMany : public RuleDecorator
	{
		virtual ~Repeat_OneToMany() {}
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