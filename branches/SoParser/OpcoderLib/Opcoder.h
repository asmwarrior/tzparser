#ifndef __SO_OPCODER_H__
#define __SO_OPCODER_H__

#include "RulesVisitor.h"
#include "Rule.h"

#include "OpcodePart.h"
#include "OpcoderInfos.h"

#include <iostream>

#include <map>
#include <queue>

namespace SoParse
{
	class Opcoder : public IRulesVisitor
	{
	public:
		Opcoder() : _inRule(false), _args(0), _argsSize(0) {}
		virtual	~Opcoder() {}

		virtual bool	enter(IRule * rule, bool hasChild = true);
		virtual void	leave(IRule * rule);

		void			createOpcode(APIRule r);

		void			disp(std::ostream& os);
		void			save(std::ostream& os);

	private:
		void			clean(void);
		void			setRefs(void);
		bool			cleanRefs(void);

		void			setArgs(void);

		std::string		labelPos(int p);

		OpcodePart _opc;

		typedef std::map<IRule *, unsigned short int> mapLPIruleShortInt;
		mapLPIruleShortInt _ruleRefs;

		typedef std::map<unsigned short int, IRule *> mapShortIntLPIrule;
		mapShortIntLPIrule _waitingRefs;

		bool _inRule;

		typedef std::queue<IRule *> queueLPIRule;
		queueLPIRule _rulesToGen;

		char * _args;
		unsigned int _argsSize;

		OpcoderInfos	_infos;
	};
}

#endif  // !__SO_OPCODER_H__
