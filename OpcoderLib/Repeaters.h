#ifndef __SO_REPEATERS_H__
#define __SO_REPEATERS_H__

#include "RuleDecorator.h"
#include "Opcodes.h"

namespace SoParse
{
	class Repeater : public RuleDecorator
	{
	public:
		virtual ~Repeater() {}
	};

	class Repeat_ZeroOrOne : public Repeater
	{
		virtual ~Repeat_ZeroOrOne() {}

		virtual std::string getName() const { return "#Repeat(!)"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return new OpcodePart(IGNORE); }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return new OpcodePart(SET_REG, 0, 1); }
	};

	class Repeat_ZeroToMany : public Repeater
	{
		virtual ~Repeat_ZeroToMany() {}

		virtual std::string getName() const { return "#Repeat(*)"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return (new OpcodePart(IGNORE))->addLabelHere((int)this); }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return (new OpcodePart(IF, 0, 0))
																				->addOpcode(GO_TO)->setRefHere((int)this)
																				->addOpcode(SET_REG, 0, 1); }
	};

	class Repeat_OneToMany : public Repeater
	{
		virtual ~Repeat_OneToMany() {}

		virtual std::string getName() const { return "#Repeat(+)"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return (new OpcodePart(ADD_REPEAT, 0, 1))
																				->addOpcode(SKIP_NEXT)
																				->addOpcode(DEC_REPEAT)->addLabelHere((int)this)
																				->addOpcode(IGNORE); }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return (new OpcodePart(IF, 0, 0))
																				->addOpcode(GO_TO)->setRefHere((int)this)
																				->addOpcode(IF_NOT, 1)
																				->addOpcode(SET_REG, 0, 1)
																				->addOpcode(POP_REPEAT); }
	};

	RuleDecorator * Repeat(char c)
	{
		switch (c)
		{
		case '?':
		case '!':
			return new Repeat_ZeroOrOne;
			break;
		case '*':
			return new Repeat_ZeroToMany;
			break;
		case '+':
			return new Repeat_OneToMany;
			break;
		}
		return 0;
	}
	#define _r(c) Repeat(c)

	inline APIRule operator + (APIRule r)
	{
		return r << new Repeat_OneToMany;
	}

	inline APIRule operator * (APIRule r)
	{
		return r << new Repeat_ZeroToMany;
	}

	inline APIRule operator ! (APIRule r)
	{
		return r << new Repeat_ZeroOrOne;
	}
}

#endif  // !__SO_REPEATERS_H__