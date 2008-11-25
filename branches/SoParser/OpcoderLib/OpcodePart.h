#ifndef __SO_OPCODE_PART_H__
#define __SO_OPCODE_PART_H__

#include <list>

namespace SoParse
{
	union Opcode
	{
		struct
		{
			char	cmd;
			char	arg1;
			char	arg2;
		} a;

		struct
		{
			char		cmd;
			short int	ref;
		} r;

		Opcode(char cmd, char arg1, char arg2) { set(cmd, arg1, arg2); }
		Opcode(char cmd, short int ref) { set(cmd, ref); }

		void	set(char cmd, char arg1, char arg2) { a.cmd = cmd; a.arg1 = arg1; a.arg2 = arg2; }
		void	set(char cmd, short int ref) { r.cmd = cmd; r.ref = ref; }
	};

	struct OpcodePart
	{
		OpcodePart(char cmd, char arg1, char arg2) { addOpcode(cmd, arg1, arg2); }
		OpcodePart(char cmd, short int ref) { addOpcode(cmd, ref); }

		OpcodePart & operator += (OpcodePart & opcp)
		{
			opcodes.splice(opcodes.end(), opcp.opcodes);
			strings.splice(strings.end(), opcp.strings);
		}

		OpcodePart & addOpcode(char cmd, char arg1, char arg2) { opcodes.push_back(Opcode(cmd, arg1, arg2)); return *this; }
		OpcodePart & addOpcode(char cmd, short int ref) { opcodes.push_back(Opcode(cmd, ref));  return *this; }

		OpcodePart & addString(short int ref, std::string str) { strings.push_back(pairShortIntString(ref, str)); }

		typedef	std::list<Opcode> listChar3;
		listChar3	opcodes;

		typedef std::pair<short int, std::string> pairShortIntString;
		typedef std::list<pairShortIntString> listPairShortIntString;
		listPairShortIntString strings;
	};
}

#endif  // !__SO_OPCODE_PART_H__
