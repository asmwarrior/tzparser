/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSE_AST_H__
#define	TZ_PARSE_AST_H__

#include <string>

#include "crtdbg.h"

namespace tzParse
{
	class IParseASTElement;

	class IParseASTNode
	{
	public:
		virtual	~IParseASTNode() {}

		virtual	void				addChild(IParseASTElement*) = 0;
	};

	class IParseASTElement : public IParseASTNode
	{
	public:
		virtual	~IParseASTElement() {}

		virtual void				setAttribute(const std::string&, const std::string&) = 0;

		virtual bool				isTemp(void) { return false; }
	};

	class IParseASTDocument : public IParseASTNode
	{
	public:
		virtual	~IParseASTDocument() {}

		virtual IParseASTElement*	createElement(const std::string&) = 0;
	};
}

#endif	// !TZ_PARSE_AST_H__
