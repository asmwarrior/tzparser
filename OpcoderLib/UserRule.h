#ifndef __SO_USER_RULE_H__
#define __SO_USER_RULE_H__

#include "StandardRule.h"
#include "RuleGroup.h"

namespace SoParse
{
	#define Rule(name)	UserRule name(#name) ; name

	class UserRule : public StandardRule
	{
	public:
		virtual ~UserRule() {}
		UserRule(const char * name) : _name(name), _rules(new RuleGroupAND) {}

		virtual char const *	getName() const { return _name; }

		UserRule &				operator = (APIRule r) { _rules->push(r); return *this; };

	private:
		char const * const	_name;
		APRuleGroup			_rules;
	};

}

#endif  // !__SO_USER_RULE_H__
