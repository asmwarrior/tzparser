#ifndef __SO_OPCODER_H__
#define __SO_OPCODER_H__

#include "RulesVisitor.h"

#include "OpcodePart.h"

#include <iostream>

#include <map>
#include <queue>

namespace SoParse
{
	class Opcoder : public IRulesVisitor
	{
	public:
		Opcoder() : _inRule(false) {}
		virtual	~Opcoder() {}

		virtual bool	enter(IRule * rule, bool hasChild = true);
		virtual void	leave(IRule * rule);

		void			disp();

	private:
		void			fillOpcode(OpcodePart * opcp, bool surround = true);

		OpcodePart	_opc;

		typedef std::map<IRule *, short int> mapLPIruleShortInt;
		mapLPIruleShortInt _ruleRefs;

		typedef std::map<short int, IRule *> mapShortIntLPIrule;
		mapShortIntLPIrule _waitingRefs;

		bool	_inRule;
		
		typedef std::queue<IRule *> queueLPIRule;
		queueLPIRule	_rulesToGen;
	};
}

#endif  // !__SO_OPCODER_H__