#ifndef MIECCOMPILER_H
#define MIECCOMPILER_H

#include <vector>
#include <string>

#include "Object.h"

using StringVector = std::vector<std::string>;

class MIECCompiler : public Object
{
public:
	/**
	* <summary> Constructor. </summary>
	*
	* <param name="inputFiles"> A vector containing the paths to the input files that will be compiled. </param>
	*/
	MIECCompiler(StringVector inputFiles);

	/**
	* <summary> Compiles the input files and outputs iex files for execution on Prol16. </summary>
	*/
	void Compile();	

private:
	StringVector _inputFiles;

	std::string const logFilename = "MIECCompiler_result.txt";

};

#endif
