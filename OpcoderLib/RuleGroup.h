#ifndef __SO_RULE_GROUP_H__
#define __SO_RULE_GROUP_H__

#include "AutoPtr.h"
#include "Rule.h"
#include "GroupInsides.h"

#include <deque>

namespace SoParse
{
	typedef SoUtil::AutoPtr<IRule>	APIRule;
	typedef std::deque<APIRule>		DequeAPIRule;

	class RuleGroup : public DequeAPIRule, public IRule
	{
	public:
		virtual ~RuleGroup() {}

		virtual IRule::type getType() const { return IRule::INTERNAL; }

		virtual APIRule	groupizeAND(APIRule self, APIRule r)
		{
			this->pushRule(r);
			return self;
		}

		virtual APIRule	groupizeOR(APIRule self, APIRule r)
		{
			this->pushRule(r);
			return self;
		}

		virtual void pushRule(APIRule r) = 0;

		virtual void	acceptVisitor(IRulesVisitor * visitor)
		{
			visitor->enter(this);
			for (RuleGroup::iterator i = this->begin(); i != this->end(); ++i)
			{
				(*i)->acceptVisitor(visitor);
			}
			visitor->leave(this);
		}
	};

	typedef SoUtil::AutoPtr<RuleGroup> APRuleGroup;

	class RuleGroupAND : public RuleGroup
	{
	public:
		virtual ~RuleGroupAND() {}
		virtual std::string getName() const { return "_GroupAND"; }

		virtual bool	needRepeater() { return false; }

		virtual void pushRule(APIRule r)
		{
			if (r->needRepeater())
				r = r << new Inside_AND();
			this->push_back(r);
		}

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return 0; }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return 0; }
	};

	class RuleGroupOR : public RuleGroup
	{
	public:
		virtual ~RuleGroupOR() {}
		virtual std::string getName() const { return "_GroupOR"; }

		virtual void pushRule(APIRule r)
		{
			if (r->needRepeater())
				r = r << new Inside_OR(this);
			this->push_back(r);
		}

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return &(new OpcodePart(IGNORE))->addOpcode(SAVE_CONTEXT); }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return new OpcodePart(CANCEL_CONTEXT); }
	};
}

#endif  // !__SO_RULE_GROUP_H__
