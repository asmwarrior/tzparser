#include "UserRule.h"
#include "ReadChar.h"
#include "Repeaters.h"

#include "DispAST.h"

using namespace SoParse;

int	main()
{
// 	simpleCString	::=
// 		'"' #ReadChar('a', 'z') '"'
// 	;
	Rule(SimpleCString) =
			ReadChar('"')
		&	ReadChar('a', 'z')
		&	ReadChar('"')
	;

// 	IdentifierStart ::=
// 		#ReadChar('a', 'z') | #ReadChar('A', 'Z') | #ReadChar('_')
// 	;
	Rule(IdentifierStart) =
			ReadChar('a', 'z')
		|	ReadChar('A', 'Z')
		|	ReadChar('_')
	;

// 	Repeaters	::=
// 		#ReadChar('a')+ #ReadChar('b')? #ReadChar('c') #readChar('d')*
// 	;
	Rule(Repeater) =
			ReadChar('a') << Repeat('+')
		&	ReadChar('b') << Repeat('?')
		&	ReadChar('c')
		&	ReadChar('d') << Repeat('*')
	;

// 	IdentifierEnd ::=
// 		[#ReadChar('a', 'z') | #ReadChar('A', 'Z') | #ReadChar('0', '9') | #ReadChar('_')]*
// 	;
	Rule(IdentifierEnd) =
		(
				ReadChar('a', 'z')
			|	ReadChar('A', 'Z')
			|	ReadChar('0', '9')
			|	ReadChar('_')
		) << Repeat('*')
	;

// 	Identifier	::=
// 		IdentifierStart IdentifierEnd
// 	;
	Rule(Identifier) =
			IdentifierStart
		&	IdentifierEnd
	;

// 	GroupWithRepeaters	::=
// 		#ReadChar('a')+ | #ReadChar('b')? | #ReadChar('c') | #readChar('d')*
// 	;
	Rule(GroupWithRepeaters) =
			ReadChar('a') << Repeat('+')
		|	ReadChar('b') << Repeat('?')
		|	ReadChar('c')
		|	ReadChar('d') << Repeat('*')
	;

//	RecursiveRule	::=
//		Identifier | #ReadChar('_') RecursiveRule
//	;

	Rule(RecursiveRule) =
			Identifier
		|(
				ReadChar('_')
			&	RecursiveRule
		)
	;

	DispAST	disp;
	RecursiveRule->acceptVisitor(&disp);
}
