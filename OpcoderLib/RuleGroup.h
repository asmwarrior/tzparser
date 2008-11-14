#ifndef __SO_RULE_GROUP_H__
#define __SO_RULE_GROUP_H__

#include "AutoPtr.h"

#include <queue>

namespace SoParse
{
	class IRule;
	typedef SoUtil::AutoPtr<IRule>	APIRule;
	typedef std::queue<APIRule>		QueueAPIRule;

	class RuleGroup : public QueueAPIRule, public IRule
	{
	}

	class RuleGroupAND : public RuleGroup
	{
	public:
		virtual char const * getName() const { return "GroupAND" };
	};

	class RuleGroupOR : public RuleGroup
	{
	public:
		virtual char const * getName() const { return "GroupOR" };
	};
}

#endif  // !__SO_RULE_GROUP_H__
