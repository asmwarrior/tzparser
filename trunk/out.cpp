/*
  This file was generated using TzParser,
  which was created by salomon . brys @gmail . com
  This file is under TzLicence which is a MPL / LGPL / GPL Licence
  with some simple restrictions.
  YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
  PERMISSION OF IT'S GENERATOR AUTHOR.
*/

#include "out.h"




//	BNFIgnore		::=
//		[
//			#GetChar(P_BLANKS)
//		|
//			BNFIgnCom
//		]
//	;
RULE_IMPLEMENT(BNFIgnore, p)
{
	p	>>	( G_OR
			>>	GetChar().in(P_BLANKS).r()
			>>	BNFIgnCom().r()
			).r()
		;
	RULE_RETURN(p);
}

//	BNFLIgnore		::=
//		[
//			#GetChar(P_LBLANKS)
//		|
//			BNFIgnCom
//		]
//	;
RULE_IMPLEMENT(BNFLIgnore, p)
{
	p	>>	( G_OR
			>>	GetChar().in(P_LBLANKS).r()
			>>	BNFIgnCom().r()
			).r()
		;
	RULE_RETURN(p);
}

//	BNFIgnCom		::=
//		[
//			"//" #ReadUntil('\n')
//		|
//			"/*" #ReadUntil("*/")
//		]
//	;
RULE_IMPLEMENT(BNFIgnCom, p)
{
	p	>>	( G_OR
			>>	( G_AND
				>>	Read().str("//").r()
				>>	Read().until("\n").r()
				).r()
			>>	( G_AND
				>>	Read().str("/*").r()
				>>	Read().until("*/").r()
				).r()
			).r()
		;
	RULE_RETURN(p);
}


//	BNFRule			::=
//		Identifier:<Name>
//		"::="
//		BNFRuleCall+:!RuleCall
//		>Force("Expected ';' to end rule definition") ';'
//	;
RULE_IMPLEMENT(BNFRule, p)
{
	p	>>	Identifier().saveAttr("Name").r()
		>>	Read().str("::=").r()
		>>	BNFRuleCall().n('+').saveNode("RuleCall", false).r()
		>>	GetChar().only(';').force("Expected ';' to end rule definition").r()
		;
	RULE_RETURN(p);
}

//	BNFRuleCall		::=
//		BNFTzModifPrec*
//		BNFRuleCheck?:!Check
//		[
//			'[' BNFRuleCallIn ']'
//		|
//			BNFRuleCallIn
//		]
//		>NoIgnore BNFRepeat?
//		BNFTreeSave*:!TreeSave
//	;
RULE_IMPLEMENT(BNFRuleCall, p)
{
	p	>>	BNFTzModifPrec().n('*').r()
		>>	BNFRuleCheck().n('?').saveNode("Check", false).r()
		>>	( G_OR
			>>	( G_AND
				>>	GetChar().only('[').r()
				>>	BNFRuleCallIn().r()
				>>	GetChar().only(']').r()
				).r()
			>>	BNFRuleCallIn().r()
			).r()
		>>	BNFRepeat().ignoreBefore(false).n('?').r()
		>>	BNFTreeSave().n('*').saveNode("TreeSave", false).r()
		;
	RULE_RETURN(p);
}

//	BNFRuleCallIn	::=
//		[
//			BNFLitteral:<Type "Litteral">
//		|
//			BNFTzRule:<Type "TzRule">
//		|
//			BNFGroup:<Type "Group">
//		]
//	;
RULE_IMPLEMENT(BNFRuleCallIn, p)
{
	p	>>	( G_OR
			>>	BNFLitteral().saveAttr("Type", "Litteral").r()
			>>	BNFTzRule().saveAttr("Type", "TzRule").r()
			>>	BNFGroup().saveAttr("Type", "Group").r()
			).r()
		;
	RULE_RETURN(p);
}

//	BNFRuleCheck	::=
//		[
//			'=':<Verif "true">
//		|
//			'!':<Verif "false">
//		]
//	;
RULE_IMPLEMENT(BNFRuleCheck, p)
{
	p	>>	( G_OR
			>>	GetChar().only('=').saveAttr("Verif", "true").r()
			>>	GetChar().only('!').saveAttr("Verif", "false").r()
			).r()
		;
	RULE_RETURN(p);
}

//	BNFString		::=
//		Identifier:<Name>
//		'='
//		BNFLitteral
//		';'
//	;
RULE_IMPLEMENT(BNFString, p)
{
	p	>>	Identifier().saveAttr("Name").r()
		>>	GetChar().only('=').r()
		>>	BNFLitteral().r()
		>>	GetChar().only(';').r()
		;
	RULE_RETURN(p);
}


//	BNFTzInstruction	::=
//		'@'
//		Identifier:<Name>
//		BNFTzArgs
//		';'
//	;
RULE_IMPLEMENT(BNFTzInstruction, p)
{
	p	>>	GetChar().only('@').r()
		>>	Identifier().saveAttr("Name").r()
		>>	BNFTzArgs().r()
		>>	GetChar().only(';').r()
		;
	RULE_RETURN(p);
}

//	BNFTzRule		::=
//		[
//			'#'
//			>NoIgnore Identifier:<Name>
//			BNFTzArgs?
//		]:!TzRule.
//	;
RULE_IMPLEMENT(BNFTzRule, p)
{
	p	>>	( G_AND
			>>	GetChar().only('#').r()
			>>	Identifier().ignoreBefore(false).saveAttr("Name").r()
			>>	BNFTzArgs().n('?').r()
			).saveNode("TzRule", false).saveLine().r()
		;
	RULE_RETURN(p);
}

//	BNFTzModifPrec	::=
//		[
//			'>'
//			>NoIgnore Identifier:<Name>
//			BNFTzArgs?
//		]:!TzModif.
//	;
RULE_IMPLEMENT(BNFTzModifPrec, p)
{
	p	>>	( G_AND
			>>	GetChar().only('>').r()
			>>	Identifier().ignoreBefore(false).saveAttr("Name").r()
			>>	BNFTzArgs().n('?').r()
			).saveNode("TzModif", false).saveLine().r()
		;
	RULE_RETURN(p);
}

//	BNFTzArgs		::=
//		'('
//		[
//			BNFLitteral
//		|
//			[ '+':<Value "true"> | '-':<Value "false"> ]:!Bool
//		|
//			'0':!Null
//		]{*, ','}
//		')'
//	;
RULE_IMPLEMENT(BNFTzArgs, p)
{
	p	>>	GetChar().only('(').r()
		>>	( G_OR
			>>	BNFLitteral().r()
			>>	( G_OR
				>>	GetChar().only('+').saveAttr("Value", "true").r()
				>>	GetChar().only('-').saveAttr("Value", "false").r()
				).saveNode("Bool", false).r()
			>>	GetChar().only('0').saveNode("Null", false).r()
			).n('*', ',').r()
		>>	GetChar().only(')').r()
		;
	RULE_RETURN(p);
}


//	BNFLitteral		::=
//		[
//			[ BNFConcat:<Type "Concat"> ]:!Litteral.
//		|
//			[
//				Identifier:<Type "Identifier">
//			|
//				CStr:<Type "CStr">
//			|
//				CChar:<Type "CChar">
//			]:Litteral.
//		]
//	;
RULE_IMPLEMENT(BNFLitteral, p)
{
	p	>>	( G_OR
			>>	( G_AND
				>>	BNFConcat().saveAttr("Type", "Concat").r()
				).saveNode("Litteral", false).saveLine().r()
			>>	( G_OR
				>>	Identifier().saveAttr("Type", "Identifier").r()
				>>	CStr().saveAttr("Type", "CStr").r()
				>>	CChar().saveAttr("Type", "CChar").r()
				).saveNode("Litteral").saveLine().r()
			).r()
		;
	RULE_RETURN(p);
}

//	BNFConcat		::=
//		BNFInConcat{2,,'.'}
//	;
RULE_IMPLEMENT(BNFConcat, p)
{
	p	>>	BNFInConcat().n(2, 0, '.').r()
		;
	RULE_RETURN(p);
}

//	BNFInConcat		::=
//		[
//			Identifier:Identifier.
//		|
//			CStr:CStr.
//		|
//			CChar:CChar.
//		]
//	;
RULE_IMPLEMENT(BNFInConcat, p)
{
	p	>>	( G_OR
			>>	Identifier().saveNode("Identifier").saveLine().r()
			>>	CStr().saveNode("CStr").saveLine().r()
			>>	CChar().saveNode("CChar").saveLine().r()
			).r()
		;
	RULE_RETURN(p);
}


//	BNFRepeat		::=
//		[
//			#GetChar(BNFREPEATCHARS):<Simple>
//		|
//			BNFFullRepeat
//		]:!Need
//	;
RULE_IMPLEMENT(BNFRepeat, p)
{
	p	>>	( G_OR
			>>	GetChar().in(BNFREPEATCHARS).saveAttr("Simple").r()
			>>	BNFFullRepeat().r()
			).saveNode("Need", false).r()
		;
	RULE_RETURN(p);
}

//	BNFFullRepeat	::=
//		>Ignore(BNFLIgnore)
//		[
//			'{'
//			>Force("Incomprehensive repeat values")
//			[
//				BNFRepeatCple
//				[ ',' CChar:<Sep> ]?
//				'}'
//			|
//				BNFRepeatSple
//				[ ',' CChar:<Sep> ]?
//				'}'
//			]
//		]
//	;
RULE_IMPLEMENT(BNFFullRepeat, p)
{
	p	>>	( G_AND
			>>	GetChar().only('{').r()
			>>	( G_OR
				>>	( G_AND
					>>	BNFRepeatCple().r()
					>>	( G_AND
						>>	GetChar().only(',').r()
						>>	CChar().saveAttr("Sep").r()
						).n('?').r()
					>>	GetChar().only('}').r()
					).r()
				>>	( G_AND
					>>	BNFRepeatSple().r()
					>>	( G_AND
						>>	GetChar().only(',').r()
						>>	CChar().saveAttr("Sep").r()
						).n('?').r()
					>>	GetChar().only('}').r()
					).r()
				).force("Incomprehensive repeat values").r()
			).ignore(BNFLIgnore().r()).r()
		;
	RULE_RETURN(p);
}

//	BNFRepeatSple	::=
//		[
//			#GetChar(BNFREPEATCHARS):<Simple>
//		|
//			#Integer(+):<FixNum>
//		]
//	;
RULE_IMPLEMENT(BNFRepeatSple, p)
{
	p	>>	( G_OR
			>>	GetChar().in(BNFREPEATCHARS).saveAttr("Simple").r()
			>>	Integer().forcePositive().saveAttr("FixNum").r()
			).r()
		;
	RULE_RETURN(p);
}

//	BNFRepeatCple	::=
//		#Integer(+)?:<Min>
//		','
//		#Integer(+)?:<Max>
//	;
RULE_IMPLEMENT(BNFRepeatCple, p)
{
	p	>>	Integer().forcePositive().n('?').saveAttr("Min").r()
		>>	GetChar().only(',').r()
		>>	Integer().forcePositive().n('?').saveAttr("Max").r()
		;
	RULE_RETURN(p);
}


//	BNFTreeSave		::=
//		':'
//		>Ignore(BNFLIgnore)
//		>NoIgnore
//		[
//			BNFTreeSaveNode:<Type "Node">
//		|
//			BNFTreeSaveAttr:<Type "Attr">
//		]
//	;
RULE_IMPLEMENT(BNFTreeSave, p)
{
	p	>>	GetChar().only(':').r()
		>>	( G_OR
			>>	BNFTreeSaveNode().saveAttr("Type", "Node").r()
			>>	BNFTreeSaveAttr().saveAttr("Type", "Attr").r()
			).ignore(BNFLIgnore().r()).ignoreBefore(false).r()
		;
	RULE_RETURN(p);
}

//	BNFTreeSaveNode	::=
//		'!'?:<NoValue '1'>
//		>NoIgnore Identifier:<Name>
//		>NoIgnore '.'?:<WithLine '1'>
//	;
RULE_IMPLEMENT(BNFTreeSaveNode, p)
{
	p	>>	GetChar().only('!').n('?').saveAttr("NoValue", "1").r()
		>>	Identifier().ignoreBefore(false).saveAttr("Name").r()
		>>	GetChar().only('.').ignoreBefore(false).n('?').saveAttr("WithLine", "1").r()
		;
	RULE_RETURN(p);
}

//	BNFTreeSaveAttr	::=
//		'<'
//		Identifier:<Name>
//		BNFLitteral?:<WithValue '1'>
//		>NoIgnore
//		>Force("Expecting '>' to end Attr definition") '>'
//	;
RULE_IMPLEMENT(BNFTreeSaveAttr, p)
{
	p	>>	GetChar().only('<').r()
		>>	Identifier().saveAttr("Name").r()
		>>	BNFLitteral().n('?').saveAttr("WithValue", "1").r()
		>>	GetChar().only('>').ignoreBefore(false).force("Expecting '>' to end Attr definition").r()
		;
	RULE_RETURN(p);
}


//	BNFGroup		::=
//		'['	
//		[
//			BNFGroupOR:<Type "OR">
//		|
//			BNFGroupAND:<Type "AND">
//		]:!Group
//		>Force("Expecting ']' to end group")
//		']'
//	;
RULE_IMPLEMENT(BNFGroup, p)
{
	p	>>	GetChar().only('[').r()
		>>	( G_OR
			>>	BNFGroupOR().saveAttr("Type", "OR").r()
			>>	BNFGroupAND().saveAttr("Type", "AND").r()
			).saveNode("Group", false).r()
		>>	GetChar().only(']').force("Expecting ']' to end group").r()
		;
	RULE_RETURN(p);
}

//	BNFGroupAND		::=
//		BNFRuleCall+:!RuleCall
//	;
RULE_IMPLEMENT(BNFGroupAND, p)
{
	p	>>	BNFRuleCall().n('+').saveNode("RuleCall", false).r()
		;
	RULE_RETURN(p);
}

//	BNFGroupOR		::=
//		BNFGroupInOR{2,,'|'}
//	;
RULE_IMPLEMENT(BNFGroupOR, p)
{
	p	>>	BNFGroupInOR().n(2, 0, '|').r()
		;
	RULE_RETURN(p);
}

//	BNFGroupInOR	::=
//		[
//			BNFRuleCall !BNFRuleCall
//		|
//			[ BNFGroupAND:<Type "AND"> ]:!Group:<Type "Group">
//		]:!RuleCall
//	;
RULE_IMPLEMENT(BNFGroupInOR, p)
{
	p	>>	( G_OR
			>>	( G_AND
				>>	BNFRuleCall().r()
				>>	BNFRuleCall().check(false).r()
				).r()
			>>	( G_AND
				>>	BNFGroupAND().saveAttr("Type", "AND").r()
				).saveNode("Group", false).saveAttr("Type", "Group").r()
			).saveNode("RuleCall", false).r()
		;
	RULE_RETURN(p);
}

//	BNF				::=
//		>Ignore(BNFIgnore)
//		>Force("Could not parse rules")
//		[
//			[
//				BNFRule:Rule.
//			|
//				BNFString:!String.
//			|
//				BNFTzInstruction:!Instruction.
//			]*
//			>Force("Expected end of file") EndOfParse
//		]
//	;
RULE_IMPLEMENT(BNF, p)
{
	p	>>	( G_AND
			>>	( G_OR
				>>	BNFRule().saveNode("Rule").saveLine().r()
				>>	BNFString().saveNode("String", false).saveLine().r()
				>>	BNFTzInstruction().saveNode("Instruction", false).saveLine().r()
				).n('*').r()
			>>	EndOfParse().force("Expected end of file").r()
			).ignore(BNFIgnore().r()).force("Could not parse rules").r()
		;
	RULE_RETURN(p);
}
