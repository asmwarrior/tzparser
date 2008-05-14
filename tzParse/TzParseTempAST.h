/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSE_TEMP_AST_H__
#define	TZ_PARSE_TEMP_AST_H__

#include <queue>

#include "TzParseAST.h"

#include "generic/win32_crtdbg.h"

namespace tzParse
{
	typedef	std::pair<std::string, std::string>	stringPair;
	typedef	std::queue<stringPair>				stringPairQueue;
	typedef	std::queue<IParseASTElement*>		PTPATEQueue;

	class TzParseASTTmpEl : public IParseASTElement
	{
	public:
		virtual	~TzParseASTTmpEl()
		{
			for (; !_el.empty(); _el.pop())
				delete _el.front();
		}

		virtual	void	addChild(IParseASTElement* e)
		{
			_el.push(e);
		}

		virtual void	setAttribute(const std::string& a, const std::string& b)
		{
			_al.push(stringPair(a, b));
		}

		void			merge(IParseASTNode* parent)
		{
			for (; !_el.empty(); _el.pop())
				parent->addChild(_el.front());
		}

		void			mergeAll(IParseASTElement* parent)
		{
			for (; !_al.empty(); _al.pop())
				parent->setAttribute(_al.front().first, _al.front().second);

			for (; !_el.empty(); _el.pop())
				parent->addChild(_el.front());
		}

		virtual bool				isTemp(void) { return true; }
	private:
		stringPairQueue	_al;	
		PTPATEQueue		_el;
	};
}

#endif

