#ifndef __SO_OPCODE_PART_H__
#define __SO_OPCODE_PART_H__

#include <list>
#include <map>
#include <string>

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

		Opcode(unsigned char cmd, unsigned char arg1, unsigned char arg2) { set(cmd, arg1, arg2); }
		Opcode(unsigned char cmd, unsigned short int ref) { set(cmd, ref); }
		Opcode(unsigned char cmd) { set(cmd); }

		void	set(unsigned char cmd, unsigned char arg1, unsigned char arg2) { this->cmd = cmd; this->arg[0] = arg1; this->arg[1] = arg2; }
		void	set(unsigned char cmd, unsigned short int ref) { this->cmd = cmd; this->ref = ref; }
		void	set(unsigned char cmd) { set(cmd, 0); }

		std::string	label;
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
//			strings.splice(strings.end(), opcp.strings);
			return *this;
		}

		OpcodePart * addOpcode(unsigned char cmd, unsigned char arg1, unsigned char arg2) { opcodes.push_back(Opcode(cmd, arg1, arg2)); return this; }
		OpcodePart * addOpcode(unsigned char cmd, unsigned short int ref) { opcodes.push_back(Opcode(cmd, ref)); return this; }
		OpcodePart * addOpcode(unsigned char cmd) { opcodes.push_back(Opcode(cmd)); return this; }
		OpcodePart * addOpcode(Opcode const & o) { opcodes.push_back(o); return this; }

		OpcodePart * addRef(std::string label) { opcodes.back().label = label; return this; }

		OpcodePart * addLabel(std::string label) { labels[label] = opcodes.size() * 3; return this; }

		typedef	std::list<Opcode> listOpcode;
		listOpcode	opcodes;

		typedef std::map<std::string, unsigned short int> mapStringShortInt;
		mapStringShortInt	labels;
	};
}

#endif  // !__SO_OPCODE_PART_H__
