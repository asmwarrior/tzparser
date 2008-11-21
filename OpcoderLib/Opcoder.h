#ifndef __SO_OPCODER_H__
#define __SO_OPCODER_H__

#include "RulesVisitor.h"

#include <iostream>

namespace SoParse
{
	class Opcoder : public IRulesVisitor
	{
	public:
		virtual	~Opcoder() {}
		Opcoder(std::ostream & out) : _os(out) {}

		virtual bool	enter(IRule * rule, bool hasChild = true);
		virtual void	leave(IRule * rule);

	private:
		std::ostream &	_os;
	};
}

#endif  // !__SO_OPCODER_H__