
#ifndef __SO_IGNORE_H__
#define __SO_IGNORE_H__

#include "Rule.h"
#include "Opcodes.h"

#include "AutoPtr.h"

namespace SoParse
{
	class CIgnore : public InnocentRuleDecorator
	{
	public:
		virtual ~CIgnore() {}

		CIgnore(APIRule r) : _ignoreRule(r) {}

		virtual std::string getName() const { return "#Ignore"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return (new OpcodePart(ADD_IGNORE))->setRefHere((int)_ignoreRule); }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return new OpcodePart(POP_IGNORE); }

		virtual IRule * hasRuleRef() { return _ignoreRule; }

	private:
		APIRule _ignoreRule;
	};

	typedef SoUtil::AutoPtr<CIgnore> APCIgnore;

	RuleDecorator*	Ignore(APIRule r)
	{
		return new CIgnore(r);
	}
}

#endif  // !__SO_IGNORE_H__