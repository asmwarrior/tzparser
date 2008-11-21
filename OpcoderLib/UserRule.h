#ifndef __SO_USER_RULE_H__
#define __SO_USER_RULE_H__

#include "StandardRule.h"
#include "RuleGroup.h"

#include "AutoPtr.h"

namespace SoParse
{
	#define Rule(name)	UserRule* name##_r = new UserRule(#name); APIRule name(name##_r); *name##_r

	class UserRule : public StandardRule
	{
	public:
		virtual ~UserRule() {}
		UserRule(const char * name) : _name(name), _rules(new RuleGroupAND) {}

		virtual std::string	getName() const { return _name; }
		virtual char const * getType() const { return "rule"; }

		UserRule &				operator = (APIRule r) { _rules->push_back(r); return *this; };

		virtual void	acceptVisitor(IRulesVisitor * visitor)
		{
			bool child = visitor->enter(this);
			if (child)
			{
				for (RuleGroup::iterator i = _rules->begin(); i != _rules->end(); ++i)
					(*i)->acceptVisitor(visitor);
				visitor->leave(this);
			}
		}

		virtual std::string	getOpcodeStart() { return ""; }
		virtual std::string	getOpcodeEnd() { return ""; }
		
	private:
		char const * const	_name;
		APRuleGroup			_rules;
	};

}

#endif  // !__SO_USER_RULE_H__
