#include "OpcodePart.h"

namespace SoParse
{
	OpcodePart & OpcodePart::operator += (OpcodePart & opcp)
	{
		opcodes.splice(opcodes.end(), opcp.opcodes);

		if (!opcp.labels.empty())
			for (mapUIntLPOpcode::iterator i = opcp.labels.begin(); i != opcp.labels.end(); ++i)
				labels[i->first] = i->second;

		if (!opcp.opcodeArgs.empty())
			for (vectorAPOpcodeArg::iterator i = opcp.opcodeArgs.begin(); i != opcp.opcodeArgs.end(); ++i)
				opcodeArgs.push_back(*i);

		return *this;
	}


	bool OpcodePart::eraseOpcode(listAPOpcode::iterator position)
	{
		listAPOpcode::iterator tmp = position;
		++tmp;
		for (mapUIntLPOpcode::iterator i = labels.begin(); i != labels.end(); ++i)
			if (i->second == *position)
			{
				if (tmp == opcodes.end())
					return false;
				i->second = *tmp;
			}

		if (position != opcodes.begin())
		{
			listAPOpcode::iterator rev1 = position;
			--rev1;
			if ((*rev1)->cmd == SKIP_NEXT)
				if (!eraseOpcode(rev1))
					return false;

			if (rev1 != opcodes.begin())
			{
				listAPOpcode::iterator rev2 = rev1;
				--rev2;

				if (((*rev2)->cmd == IF || (*rev2)->cmd == IF_NOT) && (*rev2)->arg[1] == ELSE)
					(*rev2)->arg[1] = 0;
			}
		}

		opcodes.erase(position);
		return true;
	}
}