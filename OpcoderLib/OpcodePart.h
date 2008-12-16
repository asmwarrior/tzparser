#ifndef __SO_OPCODE_PART_H__
#define __SO_OPCODE_PART_H__

#include "AutoPtr.h"

#include <list>
#include <map>

#include <iostream>

namespace SoParse
{
	struct Opcode
	{
		unsigned char	cmd;
		union
		{
			unsigned char		arg[2];
			unsigned short int	ref;
		};

		Opcode(unsigned char cmd, unsigned char arg1, unsigned char arg2) : label(0), pos(0) { set(cmd, arg1, arg2); }
		Opcode(unsigned char cmd, unsigned short int ref) : label(0), pos(0) { set(cmd, ref); }
		Opcode(unsigned char cmd) : label(0), pos(0) { set(cmd); }

		void	set(unsigned char cmd, unsigned char arg1, unsigned char arg2) { this->cmd = cmd; this->arg[0] = arg1; this->arg[1] = arg2; }
		void	set(unsigned char cmd, unsigned short int ref) { this->cmd = cmd; this->ref = ref; }
		void	set(unsigned char cmd) { set(cmd, 0); }

		void	setArg(unsigned char arg1, unsigned char arg2) { this->arg[0] = arg1; this->arg[1] = arg2; }
		void	setArg(unsigned short int ref) { this->ref = ref; }

		void	setCmd(unsigned char cmd) { this->cmd = cmd; }

		unsigned int	label;

		unsigned short int	pos;
	};

	struct OpcodePart
	{
		OpcodePart() {}
		OpcodePart(unsigned char cmd, unsigned char arg1, unsigned char arg2) { addOpcode(cmd, arg1, arg2); }
		OpcodePart(unsigned char cmd, unsigned short int ref) { addOpcode(cmd, ref); }
		OpcodePart(unsigned char cmd) { addOpcode(cmd); }

		OpcodePart & operator += (OpcodePart & opcp)
		{
			opcodes.splice(opcodes.end(), opcp.opcodes);

			for (mapUIntLPOpcode::iterator i = opcp.labels.begin(); i != opcp.labels.end(); ++i)
				labels[i->first] = i->second;

			return *this;
		}

		typedef SoUtil::AutoPtr<Opcode>	APOpcode;

		OpcodePart * addOpcode(unsigned char cmd, unsigned char arg1, unsigned char arg2) { opcodes.push_back(new Opcode(cmd, arg1, arg2)); return this; }
		OpcodePart * addOpcode(unsigned char cmd, unsigned short int ref) { opcodes.push_back(new Opcode(cmd, ref)); return this; }
		OpcodePart * addOpcode(unsigned char cmd) { opcodes.push_back(new Opcode(cmd)); return this; }
		OpcodePart * addOpcode(APOpcode const o) { opcodes.push_back(o); return this; }

		OpcodePart * setRefHere(unsigned int label) { opcodes.back()->label = label; return this; }

		OpcodePart * addLabelHere(unsigned int label) { labels[label] = opcodes.back().getPtr(); return this; }

		typedef	std::list<APOpcode> listAPOpcode;
		listAPOpcode	opcodes;

		typedef std::map<unsigned int, Opcode*> mapUIntLPOpcode;
		mapUIntLPOpcode	labels;
	};
}

#endif  // !__SO_OPCODE_PART_H__
