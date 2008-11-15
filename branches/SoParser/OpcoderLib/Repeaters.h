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

	void Repeat()
	{

	}
}

#endif  // !__SO_REPEATERS_H__