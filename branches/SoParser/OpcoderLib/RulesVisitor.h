#ifndef __SO_RULES_VISITOR_H__
#define	__SO_RULES_VISITOR_H__

#include "Rule.h"

#include <string>

namespace SoParse
{
	class IRulesVisitor
	{
	public:
		virtual	~IRulesVisitor() {}

		virtual void	enter(std::string const & name) = 0;
		virtual void	leave();
	};
}

#endif
