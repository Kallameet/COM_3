#include <iostream>
#include <fstream>
#include <unordered_map>
#include <exception>

#include "MIECCompiler.h"
#include "Parser.h"
#include "CodeGenerator.h"

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
			auto tacEntries = parser._tacGenerator.GetEntries();
			CodeGenerator codeGen(tacEntries);
						
			auto iexFileName = inputFile.substr(0, inputFile.find_last_of(".")) + ".iex";
			std::ofstream iexFile(iexFileName, std::ios_base::out);

			try
			{
				codeGen.GenerateCode(iexFile);

				std::cout << "Success" << std::endl;

				log << inputFile << ": OK" << std::endl;
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else
		{
			std::cout << "Failed " << parser.errors->count << "errors detected" << std::endl;

			log << inputFile << ": FAILED: " << parser.errors->count << " error(s) detected" << std::endl;
		}
		coco_string_delete(fileName);

		log << std::endl;
	}
}