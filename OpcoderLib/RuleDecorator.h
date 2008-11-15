#ifndef __SO_RULE_DECORATOR_H__
#define __SO_RULE_DECORATOR_H__

#include "Rule.h"

namespace SoParse
{
	class RuleDecorator : public IRule
	{
	public:
		virtual ~RuleDecorator() {}

		virtual char const * getName() { return _r->getName(); }

		virtual APIRule	groupizeAND(APIRule self, APIRule r) { return _r->groupizeAND(self, r); }
		virtual APIRule	groupizeOR(APIRule self, APIRule r) { return _r->groupizeOR(self, r); }

	private:
		APIRule	_r;
	};
}

#endif  // !__SO_RULE_DECORATOR_H__
