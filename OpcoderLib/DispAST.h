#ifndef __SO_DISP_AST_H__
#define __SO_DISP_AST_H__

#include "RulesVisitor.h"

#include <iostream>
#include <iomanip>

#include <set>

namespace SoParse
{
	class DispAST : public IRulesVisitor
	{
	public:
		virtual	~DispAST() {}
		DispAST() : _indent(0) {}

		virtual bool	enter(IRule * rule, bool hasChild /* = true */)
		{
			if (hasChild && _inside.find(rule) != _inside.end())
				hasChild = false;
			_inside.insert(rule);

			std::cout << std::setfill(' ') << std::setw(_indent * 4) << "";

			std::cout << "<" << rule->getName();
			if (hasChild)
			{
				std::cout << ">";
				++_indent;
			}
			else
				std::cout << " />";

			std::cout << std::endl;

			return hasChild;
		}

		virtual void	leave(IRule * rule)
		{
			--_indent;
			std::cout << std::setfill(' ') << std::setw(_indent * 4) << ""
				<< "</" << rule->getName() << ">" << std::endl;
			_inside.erase(rule);
		}

	private:
		int		_indent;

		typedef	std::set<IRule *>	SetIRule;
		SetIRule	_inside;
	};
}

#endif  // !__SO_DISP_AST_H__