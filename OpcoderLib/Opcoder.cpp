
#include "Opcoder.h"
#include "Rule.h"

#include "Opcodes.h"

#include <iostream>
#include <iomanip>

namespace SoParse
{
	bool	Opcoder::enter(IRule * rule, bool hasChild /* = true */)
	{
		OpcodePart * opcp = rule->getOpcodeStart();
		if (opcp)
		{
			if (rule->getType() == IRule::RULE)
				;
			fillOpcode(opcp, rule->getType() != IRule::RULE);
		}
		return hasChild;
	}

	void	Opcoder::leave(IRule * rule)
	{
		OpcodePart * opcp = rule->getOpcodeEnd();
		if (opcp)
			fillOpcode(opcp, rule->getType() != IRule::RULE);
	}

	void	Opcoder::fillOpcode(OpcodePart * opcp, bool surround /* = true */)
	{
		if (surround)
			_opc.addOpcode(IGNORE);
		_opc += *opcp;
		if (surround)
			_opc.addOpcode(IF, FAIL, NO_ELSE).addOpcode(RESTORE_CONTEXT_AND_GO_BACK);
		delete opcp;
	}

	void	Opcoder::disp()
	{
		for (OpcodePart::listOpcode::iterator i = _opc.opcodes.begin(); i != _opc.opcodes.end(); ++i)
		{
			std::cout.setf(std::ios::hex, std::ios::basefield);
			std::cout
				<< std::setfill('0') << std::setw(2) << (int)(i->a.cmd) << ' '
				<< std::setfill('0') << std::setw(2) << (int)(i->a.arg1) << ' '
				<< std::setfill('0') << std::setw(2) << (int)(i->a.arg2) << std::endl;
		}
	}
}