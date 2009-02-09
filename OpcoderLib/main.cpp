#include "UserRule.h"
#include "ReadChar.h"
#include "Repeaters.h"
#include "Ignore.h"

#include "DispAST.h"

#include "Opcoder.h"

#include <iostream>
#include <sstream>

#include <fstream>

using namespace SoParse;

int	main()
{
// 	simpleCString	::=
// 		'"' #ReadChar('a', 'z') '"'
// 	;
	_R_(SimpleCString) =
			ReadChar('"')
		&	ReadChar('a', 'z')
		&	ReadChar('"')
	;

// 	IdentifierStart ::=
// 		#ReadChar('a', 'z') | #ReadChar('A', 'Z') | #ReadChar('_')
// 	;
	_R_(IdentifierStart) =
			ReadChar('a', 'z')
		|	ReadChar('A', 'Z')
		|	ReadChar('_')
	;

// 	Repeaters	::=
// 		#ReadChar('a')+ #ReadChar('b')? #ReadChar('c') #readChar('d')*
// 	;
	_R_(Repeaters) =
			+ReadChar('a')
		&	!ReadChar('b')
		&	ReadChar('c')
		&	*ReadChar('d')
	;

// 	IdentifierEnd ::=
// 		[#ReadChar('a', 'z') | #ReadChar('A', 'Z') | #ReadChar('0', '9') | #ReadChar('_')]*
// 	;
	_R_(IdentifierEnd) =
		*(
				ReadChar('a', 'z')
			|	ReadChar('A', 'Z')
			|	ReadChar('0', '9')
			|	ReadChar('_')
		)
	;

//	Blanks ::=
//		[' ' | '\t' | '\r' | '\n']+
//	;
	_R_(Blanks) =
			+ReadChar(" \t\r\n")
	;

// 	Identifier	::=
// 		IdentifierStart IdentifierEnd
// 	;
	_R_(Identifier) =
		(
			IdentifierStart
		&	IdentifierEnd
		) << Ignore(Blanks)
	;

// 	GroupWithRepeaters	::=
// 		#ReadChar('a')+ | #ReadChar('b')? | #ReadChar('c') | #readChar('d')*
// 	;
	_R_(GroupWithRepeaters) =
			+ReadChar('a')
		|	!ReadChar('b')
		|	ReadChar('c')
		|	*ReadChar('d')
	;

//	RecursiveRule	::=
//		Identifier | #ReadChar('_') RecursiveRule
//	;

	_R_(RecursiveRule) =
			Identifier
		|(
				ReadChar('_')
			&	RecursiveRule
		)
	;



	APIRule r = Identifier;

	DispAST	disp;
	r->acceptVisitor(&disp);


	Opcoder opc;
	opc.createOpcode(r);

	std::cout << "GENERATED OPCODE :" << std::endl;
	opc.disp(std::cout);

	std::ofstream outfile("../test.spo", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

	opc.save(outfile);
}
