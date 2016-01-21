#include <iostream>
#include <fstream>
#include <unordered_map>

#include "MIECCompiler.h"
#include "Parser.h"

MIECCompiler::MIECCompiler(StringVector inputFiles)
{
	_inputFiles = inputFiles;
}

void MIECCompiler::Compile()
{
	std::ofstream log(logFilename, std::ios_base::app | std::ios_base::out);
	log << "MiniIEC.exe" << std::endl;

	for (auto &inputFile : _inputFiles)
	{
		wchar_t *fileName = coco_string_create(inputFile.c_str());

		MIEC::Scanner scanner(fileName);
		MIEC::Parser parser(&scanner);

		parser.Parse();
		
		if (parser.errors->count == 0)
		{
			parser._symTab.Print(std::cout);

			std::cout << "Success" << std::endl;
			
			log << inputFile << ": OK" << std::endl;
		}
		else
		{
			std::cout << "Failed " << parser.errors->count << "errors detected" << std::endl;

			log << inputFile << ": FAILED: " << parser.errors->count << " error(s) detected" << std::endl;
		}

		coco_string_delete(fileName);
	}	

	log << std::endl;
}