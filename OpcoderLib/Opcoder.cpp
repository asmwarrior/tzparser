
#include "Opcoder.h"

#include "Rule.h"

namespace SoParse
{
	bool	Opcoder::enter(IRule * rule, bool hasChild /* = true */)
	{
		_os << rule->getOpcodeStart();
		return hasChild;
	}

	void	Opcoder::leave(IRule * rule)
	{
		_os << rule->getOpcodeEnd();
	}
}