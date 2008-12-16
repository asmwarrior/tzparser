
#include "Opcoder.h"
#include "Rule.h"

#include "Opcodes.h"

#include <iostream>
#include <iomanip>

namespace SoParse
{
	bool	Opcoder::enter(IRule * rule, bool hasChild /* = true */)
	{
		if (!_inRule && rule->getType() != IRule::RULE)
			throw "You MUST Opcode a UserRule first";

		if (_inRule && rule->getType() == IRule::RULE)
		{
			_waitingRefs[_opc.opcodes.size() * 3] = rule;
			fillOpcode(new OpcodePart(LOAD));
			_rulesToGen.push(rule);
			return false;
		}

		if (rule->getType() == IRule::RULE)
			_inRule = true;

		OpcodePart * opcp = rule->getOpcodeStart(_infos);
		if (opcp)
		{
			if (rule->getType() == IRule::RULE)
				_ruleRefs[rule] = _opc.opcodes.size() * 3;
			fillOpcode(opcp/*, rule->getType() != IRule::RULE*/);
		}

		return hasChild;
	}

	void	Opcoder::leave(IRule * rule)
	{
		OpcodePart * opcp = rule->getOpcodeEnd(_infos);
		if (opcp)
			fillOpcode(opcp, rule->getType() != IRule::RULE);

		if (rule->getType() == IRule::RULE)
		{
			_inRule = false;
			if (!_rulesToGen.empty())
			{
				IRule * ruleToGen = _rulesToGen.front();
				_rulesToGen.pop();
				if (_ruleRefs.find(ruleToGen) == _ruleRefs.end())
					ruleToGen->acceptVisitor(this);
			}
		}
	}

	void	Opcoder::setRefs()
	{
		unsigned short int pos = 0;
		for (OpcodePart::listAPOpcode::iterator i = _opc.opcodes.begin(); i != _opc.opcodes.end(); ++i)
		{
			(*i)->pos = pos;
			pos += 3;
		}

		for (OpcodePart::listAPOpcode::iterator i = _opc.opcodes.begin(); i != _opc.opcodes.end(); ++i)
			if ((*i)->label)
			{
				if (_opc.labels.find((*i)->label) == _opc.labels.end())
				{
					std::cout << "Found a reference without its label" << std::endl;
					continue ;
				}

				(*i)->setArg(_opc.labels[(*i)->label]->pos);
			}

	}

	void	Opcoder::fillOpcode(OpcodePart * opcp, bool surround /* = true */)
	{
		_opc += *opcp;
		delete opcp;
	}

	void	Opcoder::disp()
	{
		for (OpcodePart::listAPOpcode::iterator i = _opc.opcodes.begin(); i != _opc.opcodes.end(); ++i)
		{
			std::cout.setf(std::ios::hex, std::ios::basefield);
			int c;
			for (c = 0; codeNames[c].code; ++c)
				if (codeNames[c].code == (*i)->cmd)
					break ;

			std::cout << std::setfill('0') << std::setw(4) << (int)((*i)->pos) << ':' << ' ';

			std::cout << std::setfill('0') << std::setw(2) << (int)((*i)->cmd) << ' ';
			if (codeNames[c].nArgs == 1)
				std::cout << std::setfill('0') << std::setw(4) << ((*i)->ref) << ' ' << ' ';
			else
				std::cout
					<< std::setfill('0') << std::setw(2) << (int)((*i)->arg[0]) << ' '
					<< std::setfill('0') << std::setw(2) << (int)((*i)->arg[1]) << ' ';

			std::cout << ' ' << codeNames[c].name << std::endl;
		}
	}
}
