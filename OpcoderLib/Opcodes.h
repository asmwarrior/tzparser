#ifndef __SO_OPCODES_H__
#define __SO_OPCODES_H__

namespace SoParse
{
	enum Opcodes
	{
		DO_NOTHING                  = '\x00',
		SAVE_CONTEXT				= '\x01',
		RESTORE_CONTEXT				= '\x02',
		CANCEL_CONTEXT				= '\x03',

		IGNORE						= '\x10',
		SET_IGNORE					= '\x11', // unsigned short int pointing to the IGNORE rule

		READ_CHAR					= '\x20',
		READ_A_CHAR					= '\x21', // first byte = the character to read, second byte unused
		READ_CHAR_RANGE				= '\x22', // first byte = starting character, second byte = ending character
		READ_CHAR_IN				= '\x23', // unsigned short int pointing to a null terminated character array containing all the characters to read

		SET_REG						= '\x30', // first byte = the register to set, second byte = the value to set
		INC_REG						= '\x31', // first byte = the register to increase, second byte = how much to increase it
		DEC_REG						= '\x32', // first byte = the register to decrease, second byte = how much to decrease it

		IF							= '\x40', // first byte = the register to test, second byte = if there is an ELSE (0 = no, 1 = yes)
		IF_NOT						= '\x41', // first byte = the register to test, second byte = if there is an ELSE (0 = no, 1 = yes)
		SKIP_NEXT					= '\x42',

		LOAD						= '\x50', // unsigned short int pointing to the code to load 
		GO_BACK						= '\x51',
		GO_TO						= '\x52', // unsigned short int pointing to the code to go to

		ADD_REPEAT					= '\x60', // first byte = min, second byte = max
		DEC_REPEAT					= '\x61',
		POP_REPEAT					= '\x62',

		RESTORE_CONTEXT_AND_GO_BACK	= '\xE0',
		CANCEL_CONTEXT_AND_GO_BACK	= '\xE1',

		ELSE						= '\x01'
	};


	struct CodeName
	{
		unsigned char code;
		const char * name;
		int nArgs;
	};

	extern CodeName codeNames[];
}

#endif  // !__SO_OPCODES_H__
