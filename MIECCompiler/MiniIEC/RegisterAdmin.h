#ifndef REGISTERADMIN_H
#define REGISTERADMIN_H

#include "Object.h"
#include "TACEntry.h"
#include "CodeGenProl16\CodeGenProl16.h"

struct TReg {
	 TACEntry* pEntry;
	 bool free;
};

class RegisterAdmin : public Object 
{
public:
	 RegisterAdmin(MIEC::CodeGenProl16* pGenProl16);
	 int GetRegister();
	 int GetRegister(TACEntry* tacEntry);
	 int AssignRegister(TACEntry* tacEntry);
	 void FreeRegister(int regNum);
private:
	 MIEC::CodeGenProl16* _pGenProl16;
	 static size_t const _maxRegNum = 8;
	 TReg _registers[_maxRegNum];
};

#endif