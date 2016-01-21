#ifndef MIECCOMPILER_H
#define MIECCOMPILER_H

#include <vector>
#include <string>

#include "Object.h"

using StringVector = std::vector<std::string>;

class MIECCompiler : public Object
{
public:
	MIECCompiler(StringVector inputFiles);

	void Compile();	

private:
	StringVector _inputFiles;

	std::string const logFilename = "MIECCompiler_result.txt";

};

#endif
