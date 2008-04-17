/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSE_GROUP_H__
#define	TZ_PARSE_GROUP_H__

#include "TzParseRule.h"

#include "crtdbg.h"

namespace tzParse
{
	#define	GROUP_OR		ParseGroup(GROUP_TYPE_OR)
	#define	GROUP_AND		ParseGroup(GROUP_TYPE_AND)
	#define	G_OR			GROUP_OR
	#define	G_AND			GROUP_AND

	enum	groupType
	{
		GROUP_TYPE_AND	= 0,
		GROUP_TYPE_OR	= 1,
		GT_AND			= GROUP_TYPE_AND,
		GT_OR			= GROUP_TYPE_OR
	};

	typedef	AutoPtr<AParseRule>		APAParseRule;
	typedef	std::list<APAParseRule>	APAParseRuleList;

	class	ParseGroup : public AParseRule
	{
	public:
		ParseGroup(ParseValue v, groupType t = GROUP_TYPE_AND) : AParseRule(v), _type(t) {}
		ParseGroup(groupType t = GROUP_TYPE_AND) : AParseRule(), _type(t) {}
		virtual ~ParseGroup() {}

		ParseGroup&		operator << (AParseRule& r);
		ParseGroup&		operator >> (AParseRule& r) { return (*this << r); }

		virtual bool			execute(Parser& p);
		virtual const char*		getRuleName(void) const { return ((_type == GT_AND) ? "ParseGroup_AND" : "ParseGroup_OR"); }
		virtual AParseRule*		clone(void)	const { ParseGroup* ptr = new ParseGroup(); *ptr = *this; return ptr; }

		RULE_OVL_GENERIC(ParseGroup);

		ParseGroup&				t(groupType gt) { _type = gt; return *this; }

		virtual bool			getIgnoreBefore(void) const;

	private:
		APAParseRuleList	ruleList;
		groupType			_type;
	};
}

#endif	// !TZ_PARSE_GROUP_H__
