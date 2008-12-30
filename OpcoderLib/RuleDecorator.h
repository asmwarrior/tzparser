#ifndef __SO_RULE_DECORATOR_H__
#define __SO_RULE_DECORATOR_H__

#include "Rule.h"
#include "AutoPtr.h"

namespace SoParse
{
	class RuleDecorator : public IRule
	{
	public:
		virtual ~RuleDecorator() {}

		virtual IRule::type getType() const { return IRule::INTERNAL; }

		virtual APIRule	groupizeAND(APIRule self, APIRule r) { return _r->groupizeAND(self, r); }
		virtual APIRule	groupizeOR(APIRule self, APIRule r) { return _r->groupizeOR(self, r); }

		virtual void	assign(APIRule r) { _r = r; }

		virtual void	acceptVisitor(IRulesVisitor * visitor)
		{
			visitor->enter(this);
			_r->acceptVisitor(visitor);
			visitor->leave(this);
		}

	protected:
		APIRule	_r;
	};

	class InnocentRuleDecorator : public RuleDecorator
	{
	public:
		virtual ~InnocentRuleDecorator() {}
		virtual void	assign(APIRule r);

		virtual bool	innocent(void) { return true; }
	};

	inline APIRule operator << (APIRule r, RuleDecorator * d)
	{
		d->assign(r);
		return APIRule(d);
	}
}

#endif  // !__SO_RULE_DECORATOR_H__
