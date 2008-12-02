#ifndef __SO_GROUP_INSIDES_H__
#define __SO_GROUP_INSIDES_H__

#include "RuleDecorator.h"
#include "Opcodes.h"

namespace SoParse
{
	class GroupInside : public RuleDecorator
	{
	public:
		virtual ~GroupInside() {}
		virtual bool	needRepeater() { return false; }
	};

	class Inside_AND : public GroupInside
	{
	public:
		virtual ~Inside_AND() {}

		virtual std::string getName() const { return "_AND"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return new OpcodePart(IGNORE); }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return &(new OpcodePart(IF, FAIL, NO_ELSE))->addOpcode(infos.wayOut.top()); }
	};

	class RuleGroupOR;

	class Inside_OR : public GroupInside
	{
	public:
		virtual ~Inside_OR() {}
		Inside_OR(RuleGroupOR * g) : _group(g) {}

		virtual std::string getName() const { return "_OR"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return 0; }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return &(new OpcodePart(IF, FAIL, ELSE))->addOpcode(RESTORE_CONTEXT).addOpcode(GO_TO); }

	private:
		RuleGroupOR * _group;
	};
}

#endif  // !__SO_GROUP_INSIDES_H__
