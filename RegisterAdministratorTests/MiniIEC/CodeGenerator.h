#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Object.h"
#include "TACEntry.h"
#include "CodeGenProl16\CodeGenProl16.h"
#include "RegisterAdmin.h"

using namespace MIEC;

class CodeGenerator : public Object 
{
public:
	 void GenerateCode(std::ostream& os);
private:
	 typedef std::list<std::pair<WORD, TACEntry const*> > TUnresolvedJumps;
	 void OperationAdd(TACEntry* apTacEntry);
	 void OperationSubtract(TACEntry* apTacEntry);
	 void OperationMultiply(TACEntry* apTacEntry);
	 void OperationDivide(TACEntry* apTacEntry);
	 void OperationAssign(TACEntry* apTacEntry);
	 void OperationJump(TACEntry* apTacEntry, TUnresolvedJumps& arUnresolvedJumps);
	 void OperationConditionalJump(TACEntry* apTacEntry, TUnresolvedJumps& arUnresolvedJumps);
	 void OperationPrint(TACEntry* apTacEntry);

	 CodeGenProl16* _pGenProl16;
	 RegisterAdmin* _pRegAdmin;
};

#endif