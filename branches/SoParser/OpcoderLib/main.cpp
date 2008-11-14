#include "RuleGroup.h"
#include "preRules.h"

using namespace SoParse;

int	main()
{
// 	simpleCString	::=
// 		'"' #ReadChar('a', 'z') '"'
// 	;
	Rule(SimpleCString) =
			ReadAChar('"')
		&	ReadCharRange('a', 'z')
		&	ReadAChar('"')
	;

// 	IdentifierStart ::=
// 		#ReadChar('a', 'z') | #ReadChar('A', 'Z') | #ReadChar('_')
// 	;
	Rule(IdentifierStart) =
			ReadCharRange('a', 'z')
		|	ReadCharRange('A', 'Z')
		|	ReadAChar('_')
	;

// 	Repeaters	::=
// 		#ReadChar('a')+ #ReadChar('b')? #ReadChar('c') #readChar('d')*
// 	;
	Rule(Repeater) =
			ReadAChar('a') -> Repeat('+')
		&	ReadAChar('b') -> Repeat('?')
		&	ReadAChar('c')
		&	ReadAChar('d') -> Repeat('*')
	;

// 	IdentifierEnd ::=
// 		[#ReadChar('a', 'z') | #ReadChar('A', 'Z') | #ReadChar('0', '9') | #ReadChar('_')]*
// 	;
	Rule(IdentifierEnd) =
		(
				ReadCharRange('a', 'z')
			|	ReadCharRange('A', 'Z')
			|	ReadCharRange('0', '9')
			|	ReadAChar('_')
		) << Repeat('*')
	;

// 	Identifier	::=
// 		IdentifierStart IdentifierEnd
// 	;
	Rule(Identifier) =
		IdentifierStart
		IdentifierEnd
	;

// 	GroupWithRepeaters	::=
// 		#ReadChar('a')+ | #ReadChar('b')? | #ReadChar('c') | #readChar('d')*
// 	;
	Rule(GroupWithRepeaters) =
			ReadAChar('a') -> Repeat('+')
		|	ReadAChar('b') -> Repeat('?')
		|	ReadAChar('c')
		|	ReadAChar('d') -> Repeat('*')
	;
}
