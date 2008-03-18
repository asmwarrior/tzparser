/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	TZ_TINY_XML_H__
#define TZ_TINY_XML_H__

#include "tinyxml/tinyxml.h"
#include "tzParse/TzParseAST.h"

#include <string>
#include <queue>

class TzTinyXMLElement : public TiXmlElement, public tzParse::IParseASTElement
{
public:
	TzTinyXMLElement(const std::string& name) : TiXmlElement(name.c_str()) {}
	virtual	~TzTinyXMLElement() {}

	virtual	void				addChild(IParseASTElement* node) { this->InsertEndChild( *(dynamic_cast<TzTinyXMLElement*>(node)) ); delete node; }
	virtual void				setAttribute(const std::string& name, const std::string& value) { this->SetAttribute(name.c_str(), value.c_str()); }
};

class TzTinyXMLDocument : public TiXmlDocument, public tzParse::IParseASTDocument
{
public:
	virtual	~TzTinyXMLDocument() {}

	virtual	void				addChild(tzParse::IParseASTElement* node) { this->InsertEndChild( *(dynamic_cast<TzTinyXMLElement*>(node)) ); delete node; }
	virtual tzParse::IParseASTElement*	createElement(const std::string& name) { return new TzTinyXMLElement(name); }
};

#endif	// !TZ_TINY_XML_H__
