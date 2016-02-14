#include <iostream>
#include <memory>

#include "../MiniIEC/BaseType.h"
#include "../MiniIEC/VarSymbol.h"
#include "../MiniIEC/TypeSymbol.h"
#include "../MiniIEC/Parser.h"
#include "../MiniIEC/Scanner.h"

using namespace std;

using StringVector = std::vector<std::string>;

int main(int argc, char* argv[])
{
	if (argc >= 2)
	{
		
	}
	else
	{
		std::cout << "--No source file specified" << std::endl;
	}

	return 0;
}