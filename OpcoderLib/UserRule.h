#ifndef __SO_USER_RULE_H__
#define __SO_USER_RULE_H__

namespace SoParse
{
	#define Rule(name)	UserRule name(#name) ; name

	class UserRule : public IRule
	{
	public:
		UserRule(const char * name) : _name(name) {}

		virtual char const *	getName() const { return _name; }

		UserRule &				operator = (APIRule r) { _rules->push(r); return *this; };
		UserRule &				operator = (APRuleGroup g) { _rules = g; return *this; };

	private:
		char const * const	_name;
		APRuleGroup			_rules;
	};

}

#endif  // !__SO_USER_RULE_H__
