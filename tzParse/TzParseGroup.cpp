/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#include "TzParseGroup.h"
#include "TzParser.h"
#include "TzParserUtils.h"

#include "crtdbg.h"

namespace tzParse
{
	ParseGroup&		ParseGroup::operator << (AParseRule& r)
	{
		ruleList.push_back(r.clone());

		return *this;
	}

	bool		ParseGroup::execute(Parser& p)
	{
		bool		ok = false;

		for (APAParseRuleList::iterator i = ruleList.begin(); i != ruleList.end(); ++i)
		{
			ok = (p >> **i >> CheckRuleOK());

			if (ok && !(*i)->getSaveValue().empty() && (ruleList.size() == 1 || _type == GT_OR) )
				RULE_VAL_SAVE((*i)->getSaveValue());

			if (_type == GT_OR)
			{
				if (ok)
					break;
				else
					p.reinitFailBit();
			}
		}

		return ok;
	}

	bool	ParseGroup::getIgnoreBefore(void) const
	{
		return _ignoreBefore;
/*
		if (!_ignoreBefore)
			return false;
		else if (ruleList.size() >= 1)
			return ruleList.front()->getIgnoreBefore();

		return _ignoreBefore;
*/
	}
}
