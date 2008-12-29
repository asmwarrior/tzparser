#include "UserRule.h"
#include "ReadChar.h"
#include "Repeaters.h"
#include "Ignore.h"

#include "DispAST.h"

#include "Opcoder.h"

#include <iostream>
#include <sstream>

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
	Rule(Repeaters) =
			ReadChar('a') << _r('+')
		&	ReadChar('b') << _r('?')
		&	ReadChar('c')
		&	ReadChar('d') << _r('*')
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
		) << _r('*')
	;

//	Blanks ::=
//		[' ' | '\t' | '\r' | '\n']+
//	;
	Rule(Blanks) =
		(
				ReadChar(' ')
			|	ReadChar('\t')
			|	ReadChar('\r')
			|	ReadChar('\n')
		) << _r('+')
	;

// 	Identifier	::=
// 		IdentifierStart IdentifierEnd
// 	;
	Rule(Identifier) =
		(
			IdentifierStart
		&	IdentifierEnd
		) << Ignore(Blanks)
	;

// 	GroupWithRepeaters	::=
// 		#ReadChar('a')+ | #ReadChar('b')? | #ReadChar('c') | #readChar('d')*
// 	;
	Rule(GroupWithRepeaters) =
			ReadChar('a') << _r('+')
		|	ReadChar('b') << _r('?')
		|	ReadChar('c')
		|	ReadChar('d') << _r('*')
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



	APIRule r = Identifier;

	DispAST	disp;
	r->acceptVisitor(&disp);

	std::cout << "VISITING TO CREATE OPCODE" << std::endl;
	Opcoder opc;
	r->acceptVisitor(&opc);

	std::cout << "CLEANING" << std::endl;
	opc.clean();

	do 
	{
		std::cout << "SETTING REFERENCES" << std::endl;
		opc.setRefs();

		std::cout << "CLEANING REFERENCES" << std::endl;
	} while (opc.cleanRefs());

	std::cout << "GENERATED OPCODE :" << std::endl;
	opc.disp(std::cout);
}
