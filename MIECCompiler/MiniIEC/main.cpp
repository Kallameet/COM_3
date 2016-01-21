#include <iostream>
#include <memory>

#include "BaseType.h"
#include "VarSymbol.h"
#include "TypeSymbol.h"
#include "SymbolTable.h"
#include "MIECCompiler.h"


int main(int argc, char* argv[])
{	
	if (argc >= 2)
	{
		MIECCompiler compiler(StringVector(argv + 1, argv + argc));
		compiler.Compile();
	}
	else
	{
		std::cout << "--No source file specified" << std::endl;
	}

	return 0;
}