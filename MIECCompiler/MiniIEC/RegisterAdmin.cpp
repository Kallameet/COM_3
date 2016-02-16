#include <exception>

#include "RegisterAdmin.h"
#include "VarSymbol.h"
#include "ConstIntSymbol.h"

RegisterAdmin::RegisterAdmin(MIEC::CodeGenProl16* pGenProl16) : _pGenProl16(pGenProl16)
{
	for (size_t regNumber = 0; regNumber < _maxRegNum; regNumber++)
	{
		_registers[regNumber].pSymbol = nullptr;
		_registers[regNumber].free = true;
	}
}

int RegisterAdmin::GetRegister()
{	
	 for (size_t regNumber = 0; regNumber < _maxRegNum; regNumber++)
	 {
		  if (_registers[regNumber].free) 
		  {
				_registers[regNumber].pSymbol = nullptr;
				_registers[regNumber].free = false;
				return regNumber;
		  }
	 }
	 throw std::exception("No free registers.");
}

int RegisterAdmin::GetRegister(Symbol* symbol)
{
	int reg = -1;

	if (reg = FindSymbolInRegisters(symbol) != -1)
	{
		return reg;
	}

	 reg = GetRegister();

	 // variable
	 VarSymbol* varSymbol = dynamic_cast<VarSymbol*>(symbol);
	 if (varSymbol != nullptr)
	 {
		  int regLoadAddress = GetRegister();

		  _pGenProl16->LoadI(regLoadAddress, varSymbol->GetOffset());
		  _pGenProl16->Load(reg, regLoadAddress);
		  _registers[reg].pSymbol = symbol;

		  FreeRegister(regLoadAddress);
		  return reg;
	 }

	 // constant
	 ConstIntSymbol* constSymbol = dynamic_cast<ConstIntSymbol*>(symbol);
	 if (constSymbol != nullptr)
	 {
		  _pGenProl16->LoadI(reg, constSymbol->GetValue());
		  _registers[reg].pSymbol = symbol;
		  return reg;
	 }

	 throw std::exception("Register allocation is only supported for VarSymbol and ConstIntSymbol.");
}

int RegisterAdmin::AssignRegister(Symbol* symbol)
{
	if (auto reg = FindSymbolInRegisters(symbol) != -1)
	{
		return reg;
	}

	 for (size_t regNumber = 0; regNumber < _maxRegNum; regNumber++)
	 {
		  if (_registers[regNumber].free) 
		  {
				_registers[regNumber].pSymbol = symbol;
				_registers[regNumber].free = false;
				return regNumber;
		  }
	 }
	 throw std::exception("No free registers.");
}

void RegisterAdmin::FreeRegister(int regNum)
{
	 _registers[regNum].pSymbol = nullptr;
	 _registers[regNum].free = true;
}

int RegisterAdmin::FindSymbolInRegisters(Symbol* symbol)
{
	for (size_t regNumber = 0; regNumber < _maxRegNum; regNumber++)
	{
		if (_registers[regNumber].pSymbol == symbol)
		{
			return regNumber;
		}
	}
	return -1;
}