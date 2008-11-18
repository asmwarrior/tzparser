#ifndef __SO_STANDARD_RULE_H__
#define __SO_STANDARD_RULE_H__

#include "Rule.h"
#include "RuleGroup.h"

namespace SoParse
{
	class StandardRule : public IRule
	{
	public:
		virtual ~StandardRule() {}
		virtual APIRule	groupizeAND(APIRule self, APIRule r)
		{
			return this->groupize(self, r, new RuleGroupAND);
		}

		virtual APIRule	groupizeOR(APIRule self, APIRule r)
		{
			return this->groupize(self, r, new RuleGroupOR);
		}

	private:
		static APIRule	groupize(APIRule self, APIRule r, RuleGroup * g)
		{
			g->push_back(self);
			g->push_back(r);
			return APIRule(g);
		}
	};
}

#endif  // !__SO_STANDARD_RULE_H__