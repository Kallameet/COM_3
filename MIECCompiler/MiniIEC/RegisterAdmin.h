#ifndef REGISTERADMIN_H
#define REGISTERADMIN_H

#include "Object.h"
#include "TACEntry.h"
#include "CodeGenProl16\CodeGenProl16.h"

struct TRegister
{
	Symbol* pSymbol;
	bool free;
};

class RegisterAdmin : public Object
{
public:
	RegisterAdmin(MIEC::CodeGenProl16* pGenProl16);
	int GetRegister();
	int GetRegister(Symbol* symbol);
	int AssignRegister(Symbol* symbol);
	void FreeRegister(int regNum);
private:
	int FindSymbolInRegisters(Symbol * symbol);

	MIEC::CodeGenProl16* _pGenProl16;

	static size_t const _maxRegNum = 8;
	TRegister _registers[_maxRegNum];
};

#endif