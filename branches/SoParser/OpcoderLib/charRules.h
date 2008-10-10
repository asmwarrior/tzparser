#ifndef __SO_CHARRULES_H__
#define	__SO_CHARRULES_H__

namespace SoParse
{
	class	GetChar : public Rule
	{
	public:
		virtual ~GetChar() {};

		virtual RuleGroup*	getInsideRules() { return 0; }
		virtual	const char*	getOpcode() { return "c"; }
	};

	class	GetAChar : public Rule
	{
	public:
		virtual ~GetAChar() {};

		virtual RuleGroup*	getInsideRules() { return 0; }
		virtual	const char*	getOpcode()
		{
			return "c";
		}

		GetAChar&	r() { return *this; }
	};
}

#endif	// !__SO_CHARRULES_H__
