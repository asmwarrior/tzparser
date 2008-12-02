#ifndef __SO_OPCODER_INFOS_H__
#define __SO_OPCODER_INFOS_H__

#include <stack>

#include "OpcodePart.h"

namespace SoParse
{
	struct OpcoderInfos
	{
		typedef std::stack<Opcode>	stackOpcode;
		stackOpcode	wayOut;
	};
}

#endif  // !__SO_OPCODER_INFOS_H__
