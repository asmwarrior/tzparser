
#include "Opcoder.h"
#include "Rule.h"

#include "Opcodes.h"

#include <iostream>
#include <iomanip>

#include <cstring>

namespace SoParse
{
	bool	Opcoder::enter(IRule * rule, bool hasChild /* = true */)
	{
		if (!_inRule && rule->getType() != IRule::RULE)
			throw "You MUST Opcode a UserRule first";

		if (_inRule && rule->hasRuleRef())
		{
			_waitingRefs[_opc.opcodes.size() * 3] = rule->hasRuleRef();
			_rulesToGen.push(rule->hasRuleRef());

			if (rule->getType() == IRule::RULE)
			{
				_opc.addOpcode(LOAD)->setRefHere((int)rule->hasRuleRef());
				return false;
			}
		}

		OpcodePart * opcp = rule->getOpcodeStart(_infos);

		if (rule->getType() == IRule::RULE)
		{
			_inRule = true;
			if (opcp)
				/*opcp->addLabelHere((int)rule);*/
				opcp->labels[(int)rule] = opcp->opcodes.front().getPtr();
			opcp->opcodes.front()->strLabel = rule->getName();
		}

		if (opcp)
		{
			if (rule->getType() == IRule::RULE)
				_ruleRefs[rule] = _opc.opcodes.size() * 3;
			_opc += *opcp;
			delete opcp;
		}

		return hasChild;
	}

	void	Opcoder::leave(IRule * rule)
	{
		OpcodePart * opcp = rule->getOpcodeEnd(_infos);
		if (opcp)
		{
			_opc += *opcp;
			delete opcp;
		}

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

	void	Opcoder::createOpcode(APIRule r)
	{
		std::cout << "VISITING TO CREATE OPCODE" << std::endl;
		r->acceptVisitor(this);

		std::cout << "CLEANING" << std::endl;
		this->clean();

		do
		{
			std::cout << "SETTING REFERENCES" << std::endl;
			this->setRefs();

			std::cout << "CLEANING REFERENCES" << std::endl;
		} while (this->cleanRefs());

		std::cout << "INSERTING ARGUMENTS" << std::endl;
		_opc.addOpcode(OPCODE_END);
		this->setArgs();

	}

	void	Opcoder::clean(void)
	{
		// Removing multiple IGNORES
		OpcodePart::listAPOpcode::iterator prec;
		for (OpcodePart::listAPOpcode::iterator i = _opc.opcodes.begin(); i != _opc.opcodes.end(); ++i)
		{
			if ((*i)->cmd == __opc(IGNORE) && i != _opc.opcodes.begin() && (*prec)->cmd == __opc(IGNORE))
			{
				//_opc.opcodes.erase(i);
				_opc.eraseOpcode(i);
				i = prec;
			}
			prec = i;
		}
	}

	void	Opcoder::setRefs(void)
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

	bool	Opcoder::cleanRefs(void)
	{
		bool ret = false;

		OpcodePart::listAPOpcode::iterator prec;

		OpcodePart::listAPOpcode::iterator i = _opc.opcodes.begin();
		while (i != _opc.opcodes.end())
		{
			if (i != _opc.opcodes.begin() && (*prec)->cmd == GO_TO && (*prec)->ref == (*i)->pos)
			{
				if (_opc.eraseOpcode(prec))
					ret = true;
			}
			prec = i;
			++i;
		}

		return ret;
	}

	void	Opcoder::setArgs(void)
	{
		// TODOO
		for (vectorAPOpcodeArg::iterator i =  _opc.opcodeArgs.begin(); i != _opc.opcodeArgs.end(); ++i)
			_argsSize += (*i)->size;

		_args = new char[_argsSize];
		unsigned int n = 0;

		for (vectorAPOpcodeArg::iterator i =  _opc.opcodeArgs.begin(); i != _opc.opcodeArgs.end(); ++i)
		{
			memcpy(_args + n, (*i)->arg, (*i)->size);
			n += (*i)->size;
		}
	}

	void	Opcoder::disp(std::ostream& os)
	{
		os.setf(std::ios::hex, std::ios::basefield);
		for (OpcodePart::listAPOpcode::iterator i = _opc.opcodes.begin(); i != _opc.opcodes.end(); ++i)
		{
			if ((*i)->cmd == __opc(OPCODE_END))
				break ;

			int c;
			for (c = 0; codeNames[c].code; ++c)
				if (codeNames[c].code == (*i)->cmd)
					break ;

			if ((*i)->strLabel != "")
				os << std::endl << "   >" << (*i)->strLabel << std::endl;

			os << std::setfill('0') << std::setw(4) << (int)((*i)->pos) << ':' << ' ';

			os << std::setfill('0') << std::setw(2) << (int)((*i)->cmd) << ' ';
			if (codeNames[c].nArgs == 1)
				os << std::setfill('0') << std::setw(4) << ((*i)->ref) << ' ' << ' ';
			else
				os
					<< std::setfill('0') << std::setw(2) << (int)((*i)->arg[0]) << ' '
					<< std::setfill('0') << std::setw(2) << (int)((*i)->arg[1]) << ' ';

			os << ' ' << ' ' << codeNames[c].name;
			if (codeNames[c].nArgs == 1)
				os << ' ' << std::setw(4) << (*i)->ref << ' ' << '>' << labelPos((*i)->ref);
			else if (codeNames[c].nArgs == 2)
				os
					<< ' ' << std::setfill('0') << std::setw(2) << (int)((*i)->arg[0]) << ','
					<< ' ' << std::setfill('0') << std::setw(2) << (int)((*i)->arg[1]);
			os << std::endl;
		}
		os.unsetf(std::ios::basefield);
	}

	std::string	Opcoder::labelPos(int p)
	{
		for (OpcodePart::listAPOpcode::iterator i = _opc.opcodes.begin(); i != _opc.opcodes.end(); ++i)
			if ((*i)->pos == p)
				return (*i)->strLabel;
		return "";
	}

	void	Opcoder::save(std::ostream& os)
	{
		for (OpcodePart::listAPOpcode::iterator i = _opc.opcodes.begin(); i != _opc.opcodes.end(); ++i)
			os << (*i)->cmd << (*i)->arg[0] << (*i)->arg[1];
		for (unsigned int i = 0; i < _argsSize; ++i)
			os << _args[i];
	}
}
