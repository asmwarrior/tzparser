#ifndef __SO_RULE_GROUP_H__
#define __SO_RULE_GROUP_H__

#include "AutoPtr.h"
#include "Rule.h"
#include "RuleDecorator.h"

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

	template<typename TYPE_RG>
	class _InsideRuleGroup : public RuleGroup
	{
	public:
		virtual void pushRule(APIRule r)
		{
			TYPE_RG* rg = dynamic_cast<TYPE_RG*>(r.getPtr());
			if (rg)
			{
				for (TYPE_RG::iterator i = rg->begin(); i != rg->end(); ++i)
					this->pushRule(*i);
				return ;
			}
			if (!dynamic_cast<TYPE_RG::Inside*>(r.getPtr()))
				r = r << new TYPE_RG::Inside((TYPE_RG*)this);
			this->push_back(r);
		}
	};

	typedef SoUtil::AutoPtr<RuleGroup> APRuleGroup;

	class RuleGroupAND : public _InsideRuleGroup<RuleGroupAND>
	{
	public:
		virtual ~RuleGroupAND() {}
		virtual std::string getName() const { return "#GroupAND"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return 0; }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return 0; }

		virtual class Inside : public RuleDecorator
		{
		public:
			virtual ~Inside() {}
			Inside(RuleGroupAND * g) {}

			virtual std::string getName() const { return "#AND"; }

			virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return new OpcodePart(IGNORE); }
			virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return (new OpcodePart(IF_NOT, 0, 0))->addOpcode(infos.wayOut.top()); }
		};

	};

	class RuleGroupOR : public _InsideRuleGroup<RuleGroupOR>
	{
	public:
		virtual ~RuleGroupOR() {}
		virtual std::string getName() const { return "#GroupOR"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return (new OpcodePart(IGNORE))->addOpcode(SAVE_CONTEXT); }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return (new OpcodePart(CANCEL_CONTEXT))->addLabelHere((unsigned int)this); }

		virtual class Inside : public RuleDecorator
		{
		public:
			virtual ~Inside() {}
			Inside(RuleGroupOR * g) : _group(g) {}

			virtual std::string getName() const { return "#OR"; }

			virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return 0; }
			virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return (new OpcodePart(IF_NOT, 0, ELSE))->addOpcode(RESTORE_CONTEXT)->addOpcode(GO_TO)->setRefHere((unsigned int)_group + 0); }

		private:
			RuleGroupOR * _group;
		};
	};
}

#endif  // !__SO_RULE_GROUP_H__
