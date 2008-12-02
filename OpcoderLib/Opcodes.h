#ifndef __SO_OPCODES_H__
#define __SO_OPCODES_H__

namespace SoParse
{
	enum Opcodes
	{
		SAVE_CONTEXT				= '\x01',
		RESTORE_CONTEXT				= '\x02',
		CANCEL_CONTEXT				= '\x03',

		IGNORE						= '\x10',
		SET_IGNORE					= '\x11', // unsigned short int pointing to the IGNORE rule

		READ_CHAR					= '\x20',
		READ_A_CHAR					= '\x21', // first byte = the character to read, second byte unused
		READ_CHAR_RANGE				= '\x22', // first byte = starting character, second byte = ending character
		READ_CHAR_IN				= '\x23', // unsigned short int pointing to a null terminated character array containing all the characters to read

		SET_SF						= '\x30', // first byte = 0 to set FAIL, 1 to set SUCCESS, second byte unused

		IF							= '\x40', // first byte = what to test (FAIL or SUCCESS), second byte = if there is an ELSE (0 = no, 1 = yes)

		LOAD						= '\x50', // unsigned short int pointing to the code to load 
		GO_BACK						= '\x51',
		GO_TO						= '\x52', // unsigned short int pointing to the code to go to

		RESTORE_CONTEXT_AND_GO_BACK	= '\xE0',
		CANCEL_CONTEXT_AND_GO_BACK	= '\xE1',

		FAIL						= '\x00',
		SUCCESS						= '\x01',

		NO_ELSE						= '\x00', // (default)
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
