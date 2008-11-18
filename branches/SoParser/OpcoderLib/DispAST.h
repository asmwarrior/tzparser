#ifndef __SO_DISP_AST_H__
#define __SO_DISP_AST_H__

#include "RulesVisitor.h"

#include <iostream>
#include <iomanip>

namespace SoParse
{
	class DispAST : public IRulesVisitor
	{
	public:
		virtual	~DispAST() {}
		DispAST() : _indent(0) {}

		virtual void	enter(IRule * rule, bool hasChild /* = true */)
		{
			std::cout << std::setfill(' ') << std::setw(_indent * 4) << "";
			if (hasChild)
			{
				std::cout << "ENTER ";
				++_indent;
			}
			else
				std::cout << "EXEC ";
			std::cout << rule->getName() << std::endl;
		}

		virtual void	leave()
		{
			--_indent;
			std::cout << std::setfill(' ') << std::setw(_indent * 4) << ""
				<< "LEAVE" << std::endl;
		}

	private:
		int		_indent;
	};
}

#endif  // !__SO_DISP_AST_H__