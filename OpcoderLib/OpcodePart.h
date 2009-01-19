#ifndef __SO_OPCODE_PART_H__
#define __SO_OPCODE_PART_H__

#include "AutoPtr.h"

#include <map>
#include <vector>
#include <list>

#include <iostream>

#include "Opcodes.h"

namespace SoParse
{
	struct OpcodeArg
	{
		OpcodeArg(const char * str) { construct(str, strlen(str) + 1); }
		OpcodeArg(const char * str, unsigned int len) { construct(str, len); }

		virtual ~OpcodeArg() { delete arg; }

		char * arg;
		unsigned int size;

	private:
		void	construct(const char * str, unsigned int len) { arg = new char[len]; memcpy(arg, str, len); size = len; }
	};

	typedef SoUtil::AutoPtr<OpcodeArg> APOpcodeArg;

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

		unsigned int label;
		unsigned short int	pos;
		APOpcodeArg refArg;

		std::string	strLabel;
	};

	typedef std::map<unsigned int, Opcode*> mapUIntLPOpcode;
	typedef std::vector<APOpcodeArg> vectorAPOpcodeArg;

	struct OpcodePart
	{
		OpcodePart() {}
		OpcodePart(unsigned char cmd, unsigned char arg1, unsigned char arg2) { addOpcode(cmd, arg1, arg2); }
		OpcodePart(unsigned char cmd, unsigned short int ref) { addOpcode(cmd, ref); }
		OpcodePart(unsigned char cmd) { addOpcode(cmd); }

		OpcodePart & operator += (OpcodePart & opcp);

		typedef SoUtil::AutoPtr<Opcode>	APOpcode;
		typedef std::list<APOpcode> listAPOpcode;

		OpcodePart * addOpcode(unsigned char cmd, unsigned char arg1, unsigned char arg2) { opcodes.push_back(new Opcode(cmd, arg1, arg2)); return this; }
		OpcodePart * addOpcode(unsigned char cmd, unsigned short int ref) { opcodes.push_back(new Opcode(cmd, ref)); return this; }
		OpcodePart * addOpcode(unsigned char cmd) { opcodes.push_back(new Opcode(cmd)); return this; }
		OpcodePart * addOpcode(APOpcode const o) { opcodes.push_back(o); return this; }

		OpcodePart * setRefHere(unsigned int label) { opcodes.back()->label = label; return this; }

		OpcodePart * addLabelHere(unsigned int label) { labels[label] = opcodes.back().getPtr(); return this; }

		OpcodePart * addRefArgHere(std::string str) { addRefArgHere(new OpcodeArg(str.c_str())); return this; }
		OpcodePart * addRefArgHere(const char * str, int len) { addRefArgHere(new OpcodeArg(str, len)); return this; }
		OpcodePart * addRefArgHere(APOpcodeArg arg) { opcodeArgs.push_back(arg); opcodes.back()->refArg = arg; return this; }

		bool eraseOpcode(listAPOpcode::iterator position);

		listAPOpcode	opcodes;

		mapUIntLPOpcode	labels;

		vectorAPOpcodeArg opcodeArgs;
	};
}

#endif  // !__SO_OPCODE_PART_H__
