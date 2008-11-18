#ifndef __SO_RULE_GROUP_H__
#define __SO_RULE_GROUP_H__

#include "AutoPtr.h"
#include "Rule.h"

#include <deque>

namespace SoParse
{
	typedef SoUtil::AutoPtr<IRule>	APIRule;
	typedef std::deque<APIRule>		DequeAPIRule;

	class RuleGroup : public DequeAPIRule, public IRule
	{
	public:
		virtual ~RuleGroup() {}
		virtual APIRule	groupizeAND(APIRule self, APIRule r)
		{
			this->push_back(r);
			return self;
		}

		virtual APIRule	groupizeOR(APIRule self, APIRule r)
		{
			this->push_back(r);
			return self;
		}

		virtual void	acceptVisitor(IRulesVisitor * visitor)
		{
			visitor->enter(this);
			for (RuleGroup::iterator i = this->begin(); i != this->end(); ++i)
			{
				(*i)->acceptVisitor(visitor);
			}
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
}

#endif  // !__SO_RULE_GROUP_H__
