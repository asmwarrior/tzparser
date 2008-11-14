#ifndef __SO_RULE_H__
#define __SO_RULE_H__

#include "RuleGroup.h"

#include "AutoPtr.h"

namespace SoParse
{
	class IRule;
	typedef SoUtil::AutoPtr<IRule>	APIRule;

	typedef SoUtil::AutoPtr<RuleGroup>	APRuleGroup;

	class IRule
	{
	public:
		virtual char const * getName() const = 0;
	};

	inline	APRuleGroup operator & (APIRule r1, APIRule r2)
	{
		APRuleGroup	g(new RuleGroupAND);

		g->push(r1);
		g->push(r2);

		return g;
	}

	inline	APRuleGroup & operator & (APRuleGroup & g, APIRule r)
	{
		g->push(r);

		return g;
	}
}

#endif  // !__SO_RULE_H__
