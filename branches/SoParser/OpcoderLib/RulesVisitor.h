#ifndef __SO_RULES_VISITOR_H__
#define	__SO_RULES_VISITOR_H__

#include <string>

namespace SoParse
{
	class IRule;

	class IRulesVisitor
	{
	public:
		virtual	~IRulesVisitor() {}

		virtual void	enter(IRule * rule) = 0;
		virtual void	leave();
	};
}

#endif
