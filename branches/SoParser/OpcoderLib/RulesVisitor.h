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

		virtual bool	enter(IRule * rule, bool hasChild = true) = 0;
		virtual void	leave(IRule * rule) = 0;
	};
}

#endif
