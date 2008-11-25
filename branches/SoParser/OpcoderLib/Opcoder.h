#ifndef __SO_OPCODER_H__
#define __SO_OPCODER_H__

#include "RulesVisitor.h"

#include "OpcodePart.h"

#include <iostream>

#include <deque>

namespace SoParse
{
	class Opcoder : public IRulesVisitor
	{
	public:
		virtual	~Opcoder() {}

		virtual bool	enter(IRule * rule, bool hasChild = true);
		virtual void	leave(IRule * rule);

		void			disp();

	private:
		void			fillOpcode(OpcodePart * opcp, bool surround = true);

		OpcodePart	_opc;

		typedef std::deque< std::pair<unsigned short int, std::string> > dequePairShortIntString;
		dequePairShortIntString _refs;
	};
}

#endif  // !__SO_OPCODER_H__