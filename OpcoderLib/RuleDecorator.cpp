#include "RuleDecorator.h"

#include "RuleGroup.h"

namespace SoParse
{
	void	InnocentRuleDecorator::assign(APIRule r)
	{
		_r = new RuleGroupAND;
		_r->groupizeAND(_r, r);
	}
}