#ifndef __SO_RULES_VISITOR_H__
#define	__SO_RULES_VISITOR_H__

#include <string>

#include "Rule.h"

namespace SoParse
{
	class IRule;

	class IRulesVisitor
	{
	public:
		virtual	~IRulesVisitor() {}

		virtual void	enter(IRule * rule, bool hasChild = true) = 0;
		virtual void	leave() = 0;
	};
}

#endif
