#include <iostream>
#include <memory>

#include "BaseType.h"
#include "VarSymbol.h"
#include "TypeSymbol.h"
#include "SymbolTable.h"
#include "MIECCompiler.h"
#include "Parser.h"

//#define CompileMode
#define TACTests

int main(int argc, char* argv[])
{	


	if (argc >= 2)
	{
#ifdef CompileMode

		MIECCompiler compiler(StringVector(argv + 1, argv + argc));
		compiler.Compile();

#endif


#ifdef TACTests

		auto inputFiles = StringVector(argv + 1, argv + argc);

		for (auto inputFile : inputFiles)
		{
			wchar_t *fileName = coco_string_create(inputFile.c_str());

			MIEC::Scanner scanner(fileName);
			MIEC::Parser parser(&scanner);

			parser.Parse();

			if (parser.errors->count == 0)
			{
				parser._tacGenerator.Print(std::cout);
								
				std::cout << inputFile << ": OK" << std::endl << std::endl;
			}
			else
			{
				std::cout << "Failed " << parser.errors->count << "errors detected" << std::endl;

				std::cout << inputFile << ": FAILED: " << parser.errors->count << " error(s) detected" << std::endl;
			}

			coco_string_delete(fileName);
		}

#endif

	}
	else
	{
		std::cout << "--No source file specified" << std::endl;
	}
	return 0;
}