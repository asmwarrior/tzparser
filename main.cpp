/*
  File created by Salomon BRYS : salomon . brys @ gmail . com
  This file is under TzLicence which is a MPL / LGPL / GPL Licence
  with some simple restrictions.
  YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
  PERMISSION OF IT'S AUTHOR.
*/

#include <fstream>
#include <iostream>

#include "tzParse/tzParse.h"
#include "BNFRules.h"

#include "tzParse/ASTAdapt/TzTinyXML.h"
#include "TzTiXMLPrinter.h"

#include "tclap/CmdLine.h"

#include "crtdbg.h"

using namespace tzParse;
using namespace TCLAP;
using namespace std;

class InFileName : public Constraint<string>
{
public:
	InFileName() : ifs(0) {}
	virtual	~InFileName() { if (ifs) delete ifs; }
	virtual std::string  description(void) const { return "A file that can be read."; }
	virtual std::string  shortID(void) const { return "InFileName"; }
	virtual bool  check(const string& value) const
	{
		ifs = new ifstream(value.c_str());
		if (ifs->fail())
		{
			cerr << "Could not open file " << value << endl << endl;
			delete ifs;
			ifs = 0;
			return false;
		}
		return true;
	}
	ifstream*	getIfs() const { return ifs; }

private:
	mutable ifstream*	ifs;
};

void	exec(IParseData& f, std::string outFile, bool traceXML = false, bool trace = false)
{
	Parser			p;
	stringstream	disclaimer;

	disclaimer	<<	"/*"																	<< endl
				<<	"  This file was generated using TzParser,"								<< endl
				<<	"  which was created by salomon . brys @gmail . com"					<< endl
				<<	"  This file is under TzLicence which is a MPL / LGPL / GPL Licence"	<< endl
				<<	"  with some simple restrictions."										<< endl
				<<	"  YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE"		<< endl
				<<	"  PERMISSION OF IT'S GENERATOR AUTHOR."								<< endl
				<<	"*/"																	<< endl
				<<	endl;

	TzTinyXMLDocument	d;
	p.setXMLDoc(&d);
	if (trace)
		p.trace();
	p	<<	f;
	p	>>	BNF().r();

	if (traceXML)
	{
		TiXmlPrinter printer;
		printer.SetIndent( "    " );
		d.Accept(&printer);
		cout << printer.CStr();
	}

	ofstream	outputCPP((outFile + ".cpp").c_str());
	ofstream	outputH((outFile + ".h").c_str());

	if (outputCPP.fail())
		throw ArgParseException(string("Could not open ") + outFile + ".cpp", "outFile");
	else if (outputH.fail())
		throw ArgParseException(string("Could not open ") + outFile + ".h", "outFile");

	TzTiXMLPrinter	tzPrinter(&d);

	string	define;
	for (register unsigned int i = 0; i < outFile.length(); ++i)
		define += toupper(outFile[i]);
	define += "_H__";

	outputH		<< disclaimer.str()
				<< "#ifndef\t" << define << endl
				<< "#define\t" << define << endl
				<< endl
				<< "#include \"tzParse/tzParse.h\"" << endl
				<< endl
				<< "using namespace tzParse;" << endl
				<< endl
				<< tzPrinter.getHead() << endl
				<< "#endif\t// !" << define << endl;

	outputCPP	<< disclaimer.str()
				<< "#include \"" << (outFile + ".h") << '"' << endl
				<< endl
				<< tzPrinter.getCode();
}

int	main(int argc, char*argv[])
{
//	_CrtSetBreakAlloc(42)

	try
	{
		CmdLine	cmd("TzParser generator by Salomon BRYS : salomon . brys @ gmail . com", ' ', "0.1");

		InFileName	ifnCst;
		UnlabeledValueArg<string> fileArg("inputFile", "Input BNF file. Will listen on the standard input if not defined.", false, "", &ifnCst);
		cmd.add(fileArg);

		SwitchArg xmlSwitch("x", "xml", "show the XML tree", false);
		cmd.add(xmlSwitch);

		SwitchArg traceSwitch("t", "trace", "Trace the parsing. ATTENTION : very slow !", false);
		cmd.add(traceSwitch);

		ValueArg<string> outFile("o", "outFile", "Name of the outfile (without .cpp or .h). Default to 'out' (=> out.cpp & out.h)", false, "out", "OutFileNameBody");
		cmd.add(outFile);

		cmd.parse(argc, argv);

		ParseDataIStream *f = 0;
		if (ifnCst.getIfs())
			f = new ParseDataIStream(*(ifnCst.getIfs()));
		else
			f = new ParseDataIStream(cin);

		exec(*f, outFile.getValue(), xmlSwitch.getValue(), traceSwitch.getValue());

		delete f;
	}
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "Unknown error" << endl;
	}

	_CrtDumpMemoryLeaks();

	return 0;
}