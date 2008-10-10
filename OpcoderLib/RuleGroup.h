#ifndef	__SO_RULEGROUP_H__
#define	__SO_RULEGROUP_H__

#include "IRule.h"

#include <queue>

namespace SoParse
{
	typedef std::queue<IRule*>	RuleQueue;

	class RuleGroup : public Rule
	{
	public:
		virtual	RuleGroup*	getInsideRules() { return this; }

		RuleGroup*	operator << (Rule* r) { _q.push(r); }

		RuleQueue&	getRuleQueue() { return _q; }

	private:
		RuleQueue	_q;
	};
}

#endif	// !__SO_RULEGROUP_H__
