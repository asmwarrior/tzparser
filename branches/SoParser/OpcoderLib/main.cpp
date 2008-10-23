#include "RuleGroup.h"
#include "preRules.h"

using namespace SoParse;

class StartRule : Rule
{
public:
	virtual RuleGroup*	getInsideRules()
	{
		return &(*(new RuleGroup) << GetChar
			);
	}
private:
};

int	main()
{
	StartRule	sr;

	sr.getInsideRules();
}
