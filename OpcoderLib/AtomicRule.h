#ifndef __SO_ATOMIC_RULE_H__
#define __SO_ATOMIC_RULE_H__

#include "StandardRule.h"

namespace SoParse
{
	class AtomicRule : public StandardRule
	{
	public:
		virtual ~AtomicRule() {}

		virtual void	acceptVisitor(IRulesVisitor * visitor)
		{
			visitor->enter(this, false);
		}

		virtual IRule::type getType() const { return IRule::ATOMIC; }
	};
}

#endif  // !__SO_ATOMIC_RULE_H__