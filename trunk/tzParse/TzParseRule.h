/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_PARSE_RULE_H__
#define	TZ_PARSE_RULE_H__

#include <list>
#include <string>

#include "TzParseValue.h"
#include "TzParseNeed.h"
#include "TzParserIgnore.h"

#include "generic/win32_crtdbg.h"

namespace tzParse
{
	#define RULE_DECLARE_HEAD(ruleName)	class ruleName : public AParseRule

	#define RULE_DESTRUCTOR(ruleName)	public:	virtual ~ruleName() {}

	#define	RULE_CONSTRUCTORS(ruleName)	public: ruleName(void) : AParseRule() {}									\
										public: ruleName(ParseValue v) : AParseRule(v) {}							\
										public: virtual bool	execute(Parser&);									\
										public: virtual const char*	getRuleName(void) const { return #ruleName; }

	#define RULE_HEAD(ruleName)			RULE_CONSTRUCTORS(ruleName)		\
										RULE_DESTRUCTOR(ruleName)

	#define	RULE_OVL_GENERIC(ruleName)	public: ruleName&	ignoreBefore(bool ign) { AParseRule::ignoreBefore(ign); return *this; }								\
										public: ruleName&	force(const char* m = 0) { AParseRule::force(m); return *this; }									\
										public: ruleName&	n(int min, int max, char comaSep = 0) { AParseRule::n(min, max, comaSep); return *this; }			\
										public: ruleName&	n(ParseNeed nd, char comaSep = 0) { AParseRule::n(nd, comaSep); return *this; }						\
										public: ruleName&	n(char ndc, char comaSep = 0) { AParseRule::n(ndc, comaSep); return *this; }						\
										public: ruleName&	ignore(AParseRule& r) { AParseRule::ignore(r); return *this; }										\
										public: ruleName&	ignore(const char* str) { AParseRule::ignore(str); return *this; }									\
										public: ruleName&	noIgnore(void) { AParseRule::noIgnore(); return *this; }											\
										public: ruleName&	removeIgnore(void) { AParseRule::removeIgnore(); return *this; }									\
										public: ruleName&	saveNode(const char* n, bool withVal = true) { AParseRule::saveNode(n, withVal); return *this; }	\
										public: ruleName&	saveAttr(const char* a, const char* val = 0) { AParseRule::saveAttr(a, val); return *this; }		\
										public: ruleName&	check(bool type = true) { AParseRule::check(type); return *this; }									\
										public: ruleName&	noCheck(void) { AParseRule::noCheck(); return *this; }												\
										public: ruleName&	saveLine(bool sl = true) { AParseRule::saveLine(sl); return *this; }



	#define	RULE_SIMPLE_CHAR()			public: virtual bool	simpleChar(void) const { return !_ignoreBefore; }

	#define	RULE_NO_TRACE()				public: virtual bool	traceRule(void) const { return false; }

	#define RULE_SIMPLE_CLONE(ruleName)	public: AParseRule*		clone(void) const { ruleName* ptr = new ruleName(); *ptr = *this; return ptr; }


	#define	RULE_ARG(arg, typ, def)								private: AutoInit<typ, def>	arg;
	#define	RULE_ARGNULL(arg, typ)								private: AutoInitNull<typ>	arg;

	#define	RULE_METHARG(ruleName, methName, arg, typ)			public: ruleName&	methName(typ d)			{ *arg = d; return *this; }
	#define	RULE_METHARG_DEF(ruleName, methName, arg, typ, def)	public: ruleName&	methName(typ d = def)	{ *arg = d; return *this; }

	#define	RULE_STDARG(ruleName, name, typ, def)				RULE_ARG(_##name, typ, def) RULE_METHARG(ruleName, name, _##name, typ)
	#define	RULE_STDARG_DEF(ruleName, name, typ, def, methDef)	RULE_ARG(_##name, typ, def) RULE_METHARG_DEF(ruleName, name, _##name, typ, methDef)
	#define	RULE_STDARGNULL(ruleName, name, typ)				RULE_ARGNULL(_##name, typ) RULE_METHARG(ruleName, name, _##name, typ)
	#define	RULE_STDARGNULL_DEF(ruleName, name, typ, methDef)	RULE_ARGNULL(_##name, typ) RULE_METHARG_DEF(ruleName, name, _##name, typ, methDef)


	#define RULE_DECLARE_SIMPLE(ruleName)	RULE_DECLARE_HEAD(ruleName)			\
											{									\
												RULE_HEAD(ruleName);			\
												RULE_SIMPLE_CLONE(ruleName);	\
											};


	#define	RULE_IMPLEMENT(ruleName, parserVar)	bool	ruleName::execute(Parser& parserVar)

	#define	RULE_RETURN(p)						return p >> CheckRuleOK()

	#define	RULE_VAL_SAVE(s)				_saveValue = s

	class Parser;
	class Ignore;

	typedef	AutoPtr<ParseValue>	APParseValue;
	typedef	AutoPtr<Ignore>		APIgnore;

	class AParseRule
	{
	public:
		AParseRule(void) :											_ignoreBefore(true), _force(0), _min(1), _max(1), _comaSep(0), _check(false), _checkType(true), node(0), nodeWithVal(true), attr(0), attrVal(0), svLine(false)	{}
		AParseRule(const ParseValue &v) :	val(new ParseValue(v)),	_ignoreBefore(true), _force(0), _min(1), _max(1), _comaSep(0), _check(false), _checkType(true), node(0), nodeWithVal(true), attr(0), attrVal(0), svLine(false)	{}
		virtual ~AParseRule();// {}

		void						setVal(const std::string& s) { if (val.getPtr()) val->setVal(s); }
		void						setParsevalue(const ParseValue &v) { val = new ParseValue(v); }
		void						setNoParsevalue(void) { val = 0; }
		APParseValue				getParseValue(void) { return val; }

		AParseRule&					ignoreBefore(bool ign) { _ignoreBefore = ign; return *this; }
		virtual bool				getIgnoreBefore(void) const { return _ignoreBefore; }

		AParseRule&					force(const char* m = 0) { _force = m; return *this; }
		virtual const char*			getForce(void) const { return _force; }

		AParseRule&					n(int min, int max, char comaSep = 0) { _min = min; _max = max; _comaSep = comaSep; return *this; }
		AParseRule&					n(ParseNeed nd, char comaSep = 0);
		AParseRule&					n(char ndc, char comaSep = 0);

		unsigned int				getMin(void) { return _min; }
		unsigned int				getMax(void) { return _max; }
		char						getComaSep(void) { return _comaSep; }

		AParseRule&					ignore(AParseRule& r);
		AParseRule&					ignore(const char* str);
		AParseRule&					noIgnore(void);
		AParseRule&					removeIgnore(void) { _ign = 0; return *this; }
		virtual APIgnore			getIgnore(void) { return _ign; }

		AParseRule&					saveNode(const char* n, bool withVal = true) { node = n; nodeWithVal = withVal; return *this; }
		virtual const char*			getSNode(void) { return node; }
		virtual bool				getSNodeWithVal(void) { return nodeWithVal; }
		AParseRule&					saveAttr(const char* a, const char* val = 0) { attr = a; attrVal = val; return *this; }
		virtual const char*			getSAttr(void) { return attr; }
		virtual const char*			getSAttrVal(void) { return attrVal; }
		AParseRule&					saveLine(bool sl = true) { svLine = sl; return *this; }
		virtual bool				getSaveLine(void) { return svLine; }

		AParseRule&					check(bool type = true) { _check = true; _checkType = type; return *this; }
		AParseRule&					noCheck(void) { _check = false; _checkType = true; return *this; }
		virtual bool				getCheck(void) { return _check; }
		virtual bool				getCheckType(void) { return _checkType; }

		virtual	const std::string&	getSaveValue(void) { return _saveValue; }

		virtual bool				simpleChar(void) const { return false; }
		virtual bool				traceRule(void) const { return true; }

		virtual	bool				execute(Parser&) = 0;
		virtual	AParseRule*			clone(void) const = 0;
		virtual const char*			getRuleName(void) const = 0;

		AParseRule&			r(void) { return *this; }

	protected:
		bool			_ignoreBefore;
		const char*		_force;
		unsigned int	_min;
		unsigned int	_max;
		char			_comaSep;
		APIgnore		_ign;
		std::string		_saveValue;
		bool			_check;
		bool			_checkType;

	private:
		APParseValue	val;
		const char*		node;
		bool			nodeWithVal;
		const char*		attr;
		const char*		attrVal;
		bool			svLine;
	};

	RULE_DECLARE_HEAD(GetChar)
	{
		RULE_HEAD(GetChar);
		RULE_SIMPLE_CLONE(GetChar);
		RULE_SIMPLE_CHAR();
		RULE_NO_TRACE();

		RULE_STDARGNULL(GetChar, in, const char *);

		RULE_STDARGNULL(GetChar, only, char);

		RULE_STDARGNULL(GetChar, but, char);

		RULE_STDARGNULL(GetChar, notIn, const char*);

		RULE_ARG(_caseIns, bool, false);
		RULE_METHARG_DEF(GetChar, caseInsensitive, _caseIns, bool, true);
	};

	RULE_DECLARE_HEAD(Read)
	{
		RULE_HEAD(Read);
		RULE_SIMPLE_CLONE(Read);

		RULE_STDARGNULL(Read, until, const char *);

		RULE_STDARGNULL(Read, str, const char *);

		RULE_ARG(_caseIns, bool, false);
		RULE_METHARG_DEF(Read, caseInsensitive, _caseIns, bool, true);
	};

	RULE_DECLARE_SIMPLE(EndOfParse);

}

#endif	// !TZ_PARSE_RULE_H__
