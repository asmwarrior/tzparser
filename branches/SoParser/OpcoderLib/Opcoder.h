#ifndef __SO_OPCODER_H__
#define __SO_OPCODER_H__

namespace SoParse
{
	class Opcoder : public IRulesVisitor
	{
	public:
		virtual	~Opcoder() {}

		virtual bool	enter(IRule * rule, bool hasChild = true) = 0;
		virtual void	leave(IRule * rule) = 0;
	};
}

#endif  // !__SO_OPCODER_H__