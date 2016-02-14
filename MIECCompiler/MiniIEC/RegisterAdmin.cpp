#include "RegisterAdmin.h"
#include "VarSymbol.h"
#include "ConstIntSymbol.h"

RegisterAdmin::RegisterAdmin(MIEC::CodeGenProl16* pGenProl16) : _pGenProl16(pGenProl16)
{}

int RegisterAdmin::GetRegister()
{	
	 for (int regNumber = 0; regNumber < _maxRegNum; regNumber++) {
		  if (_registers[regNumber].free) {
				_registers[regNumber].pEntry = nullptr;
				_registers[regNumber].free = false;
				return regNumber;
		  }
	 }
	 return -1;
}

int RegisterAdmin::GetRegister(TACEntry* tacEntry)
{
	 int reg = GetRegister();

	 // variable
	 VarSymbol* varSym = dynamic_cast<VarSymbol*>(tacEntry);
	 if (varSym != nullptr)
	 {
		  int regDst = GetRegister();
		  _pGenProl16->LoadI(regDst, varSym->GetOffset());
		  _pGenProl16->Load(reg, regDst);
		  _registers[reg].pEntry = tacEntry;
		  FreeRegister(regDst);
		  return reg;
	 }

	 // constant
	 ConstIntSymbol* constSym = dynamic_cast<ConstIntSymbol*>(tacEntry);
	 if (constSym != nullptr) {
		  _pGenProl16->LoadI(reg, constSym->GetValue());
		  _registers[reg].pEntry = tacEntry;
		  return reg;
	 }

	 // temporary tac entry
	 TACEntry* tacEntryTemp = dynamic_cast<TACEntry*>(tacEntry);
	 if (tacEntryTemp != nullptr) {
		  return tacEntryTemp->GetTmpResult();
	 }

	 return 0;
}

int RegisterAdmin::AssignRegister(TACEntry* tacEntry)
{
	 for (int regNumber = 0; regNumber < _maxRegNum; regNumber++) {
		  if (_registers[regNumber].free) {
				_registers[regNumber].pEntry = tacEntry;
				_registers[regNumber].free = false;
				return regNumber;
		  }
	 }
	 return -1;
}

void RegisterAdmin::FreeRegister(int regNum)
{
	 _registers[regNum].pEntry = nullptr;
	 _registers[regNum].free = true;
}