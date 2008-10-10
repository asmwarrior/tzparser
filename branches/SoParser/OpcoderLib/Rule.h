#ifndef	__SO_IRULE_H__
#define	__SO_IRULE_H__

namespace SoParse
{
	class RuleGroup;

	class	Opcode
	{
		const char*	
	};

	class Rule
	{
	public:
		virtual ~Rule() {};

		virtual RuleGroup*	getInsideRules() = 0;
		virtual const char*	getOpcode() { return 0; };
	};
}

#endif	// !__SO_IRULE_H__
