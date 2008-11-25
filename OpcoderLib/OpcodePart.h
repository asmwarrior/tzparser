#ifndef __SO_OPCODE_PART_H__
#define __SO_OPCODE_PART_H__

#include <list>

namespace SoParse
{
	union Opcode
	{
		struct
		{
			unsigned char	cmd;
			unsigned char	arg1;
			unsigned char	arg2;
		} a;

		struct
		{
			unsigned char		cmd;
			unsigned short int	ref;
		} r;

		Opcode(unsigned char cmd, unsigned char arg1, unsigned char arg2) { set(cmd, arg1, arg2); }
		Opcode(unsigned char cmd, unsigned short int ref) { set(cmd, ref); }
		Opcode(unsigned char cmd) { set(cmd); }

		void	set(unsigned char cmd, unsigned char arg1, unsigned char arg2) { a.cmd = cmd; a.arg1 = arg1; a.arg2 = arg2; }
		void	set(unsigned char cmd, unsigned short int ref) { r.cmd = cmd; r.ref = ref; }
		void	set(unsigned char cmd) { a.cmd = cmd; a.arg1 = 0; a.arg2 = 0; }
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
			strings.splice(strings.end(), opcp.strings);
			return *this;
		}

		OpcodePart & addOpcode(unsigned char cmd, unsigned char arg1, unsigned char arg2) { opcodes.push_back(Opcode(cmd, arg1, arg2)); return *this; }
		OpcodePart & addOpcode(unsigned char cmd, unsigned short int ref) { opcodes.push_back(Opcode(cmd, ref)); return *this; }
		OpcodePart & addOpcode(unsigned char cmd) { opcodes.push_back(Opcode(cmd)); return *this; }

		OpcodePart & addString(unsigned short int ref, std::string str) { strings.push_back(pairShortIntString(ref, str)); return *this; }

		typedef	std::list<Opcode> listOpcode;
		listOpcode	opcodes;

		typedef std::pair<unsigned short int, std::string> pairShortIntString;
		typedef std::list<pairShortIntString> listPairShortIntString;
		listPairShortIntString strings;
	};
}

#endif  // !__SO_OPCODE_PART_H__
