/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#include "TzParserIgnore.h"
#include "TzParseRule.h"

#include "crtdbg.h"


using namespace std;

namespace tzParse
{
  Ignore::Ignore() {}

	Ignore::Ignore(const char* str)
	{
		rule = GetChar().in(str).clone();
		normalizeRule();
	}

	Ignore::Ignore(const APAParseRule& r)
	{
		rule = r->clone();
		normalizeRule();
	}

  Ignore::Ignore(const Ignore& i)
  {
    rule = i.rule;
  }

  Ignore::~Ignore() {}

  Ignore&	Ignore::operator = (const Ignore& i)
  {
    if (this != &i)
      rule = i.rule;
    return *this;
  }

  APAParseRule	Ignore::getRule(void)
  {
    return rule;
  }

  bool		Ignore::isEmpty(void)
  {
    return (rule.getPtr() == 0);
  }

	void	Ignore::normalizeRule(void)
	{
		rule->setNoParsevalue();
		rule->n(PARSE_ONE_OR_MORE);
		rule->ignoreBefore(false);
	}
}
