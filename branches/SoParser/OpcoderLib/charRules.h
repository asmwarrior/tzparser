#ifndef __SO_CHARRULES_H__
#define	__SO_CHARRULES_H__

#include <map>

#include "Rule.h"

namespace SoParse
{
	namespace _PredefinedRules
	{
		class	_GetAChar : public Rule
		{
		public:
			_GetAChar(char c) : c(c) {}
			virtual ~_GetAChar() {}

			virtual RuleGroup*	getInsideRules() { return 0; }
			virtual	const char*	getOpcode() { return "c"; }

		private:
			char	c;
		};

		class	_GetCharRange : public Rule
		{
		public:
			_GetCharRange(char start, char end) : start(start), end(end) {}
			virtual ~_GetCharRange() {}

			virtual RuleGroup*	getInsideRules() { return 0; }
			virtual	const char*	getOpcode() { return "c"; }

		private:
			char	start;
			char	end;
		};

		class	_GetChar : public Rule
		{
			typedef	std::map<char, Rule*>		CharRuleMap;
			typedef	std::pair<char, char>		PairChar;
			typedef	std::map<PairChar, Rule*>	PairCharRuleMap;

		public:
			virtual ~_GetChar() {};

			virtual RuleGroup*	getInsideRules() { return 0; }
			virtual	const char*	getOpcode() { return "c"; }

			Rule&	operator () (char c)
			{
				if (gac.find(c) == gac.end())
					gac[c] = new _GetAChar(c);
				return *(gac[c]);
			}

			Rule&	operator () (char start, char end)
			{
				PairChar	p(start, end);
				if (gcr.find(p) == gcr.end())
					gcr[p] = new _GetCharRange(start, end);
				return *(gcr[p]);
			}

		private:
			CharRuleMap	gac;
			PairCharRuleMap	gcr;
		};
	}
}

#endif	// !__SO_CHARRULES_H__
