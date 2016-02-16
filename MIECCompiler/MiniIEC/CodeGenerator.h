#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Object.h"
#include "TACEntry.h"
#include "CodeGenProl16\CodeGenProl16.h"
#include "RegisterAdmin.h"
#include "VarSymbol.h"

using namespace MIEC;

class CodeGenerator : public Object 
{
public:
	 CodeGenerator(std::list<TACEntry*> entries);
	 ~CodeGenerator();
	 void GenerateCode(std::ostream& os);
private:
	 typedef std::list<std::pair<WORD, const int> > TUnresolvedJumps;
	 void OperationAdd(TACEntry* apTacEntry);
	 void OperationSubtract(TACEntry* apTacEntry);
	 void OperationMultiply(TACEntry* apTacEntry);
	 void OperationDivide(TACEntry* apTacEntry);
	 void OperationAssign(TACEntry* apTacEntry);
	 void OperationJump(TACEntry* apTacEntry, TUnresolvedJumps& arUnresolvedJumps);
	 void OperationIfFalseJump(TACEntry* apTacEntry, TUnresolvedJumps& arUnresolvedJumps);
	 void OperationPrint(TACEntry* apTacEntry);
	 void OperationCompare(TACEntry* apTacEntry);

	 VarSymbol* CastToVarSymbol(Symbol* symbol);
	 void SaveRegisterToMemory(int address, int inverseResults);
	 void Compare(TACEntry* apTacEntry, bool inverseComparison);
	 void CompareEquals(TACEntry* apTacEntry, int regResult, bool equals);
	 void CompareLess(TACEntry* apTacEntry, int regResult, bool inverseResults, bool inverseComparison);

	 CodeGenProl16* _pGenProl16;
	 RegisterAdmin* _pRegisterAdmin;
	 std::list<TACEntry*> _tacEntries;
};

#endif