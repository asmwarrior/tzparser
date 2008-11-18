#ifndef __SO_RULE_GROUP_H__
#define __SO_RULE_GROUP_H__

#include "AutoPtr.h"
#include "Rule.h"

#include <queue>

namespace SoParse
{
	typedef SoUtil::AutoPtr<IRule>	APIRule;
	typedef std::queue<APIRule>		QueueAPIRule;

	class RuleGroup : public QueueAPIRule, public IRule
	{
	public:
		virtual ~RuleGroup() {}
		virtual APIRule	groupizeAND(APIRule self, APIRule r)
		{
			this->push(r);
			return self;
		}

		virtual APIRule	groupizeOR(APIRule self, APIRule r)
		{
			this->push(r);
			return self;
		}

		virtual void	acceptVisitor(IRulesVisitor * visitor)
		{
			visitor->enter(this);
			visitor->leave();
		}
	};

	typedef SoUtil::AutoPtr<RuleGroup> APRuleGroup;

	class RuleGroupAND : public RuleGroup
	{
	public:
		virtual ~RuleGroupAND() {}
		virtual char const * getName() const { return "GroupAND"; }
	};

	class RuleGroupOR : public RuleGroup
	{
	public:
		virtual ~RuleGroupOR() {}
		virtual char const * getName() const { return "GroupOR"; }
	};

/*
	inline	APRuleGroup operator & (APRuleGroup g, APIRule r)
	{
		g->push(r);

		return g;
	}
*/
}

#endif  // !__SO_RULE_GROUP_H__
