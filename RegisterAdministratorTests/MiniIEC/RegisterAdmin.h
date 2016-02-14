#ifndef REGISTERADMIN_H
#define REGISTERADMIN_H

#include "Object.h"
#include "TACEntry.h"
#include "CodeGenProl16\CodeGenProl16.h"

class RegisterAdmin : public Object 
{
public:
	 RegisterAdmin(MIEC::CodeGenProl16* pGenProl16);
	 int GetRegister();
	 int GetRegister(TACEntry* dacEntry);
	 int AssignRegister(TACEntry* dacEntry);
	 void FreeRegister(int regNum);
private:
	 MIEC::CodeGenProl16* _pGenProl16;
};

#endif