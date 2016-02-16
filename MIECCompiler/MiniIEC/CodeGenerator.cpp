#include <exception>

#include "CodeGenerator.h"
#include "VarSymbol.h"
#include "ConstIntSymbol.h"

CodeGenerator::CodeGenerator(std::list<TACEntry*> entries)
{
	_pGenProl16 = new MIEC::CodeGenProl16;
	_pRegisterAdmin = new RegisterAdmin(_pGenProl16);
	for (TACEntry* entry : entries)
	{
		_tacEntries.push_back(entry);
	}
}

CodeGenerator::~CodeGenerator()
{
	delete _pGenProl16;
	delete _pRegisterAdmin;
}

void CodeGenerator::GenerateCode(std::ostream& os)
{
	TUnresolvedJumps unresolvedJumps;

	for (TACEntry* entry : _tacEntries)
	{
		entry->SetEntryAddress(_pGenProl16->GetCodePosition());
		OpKind operatorKind = entry->GetOperatorKind();

		switch (operatorKind)
		{
		case OpKind::Add:
			OperationAdd(entry);
			break;
		case OpKind::Subtract:
			OperationSubtract(entry);
			break;
		case OpKind::Multiply:
			OperationMultiply(entry);
			break;
		case OpKind::Divide:
			OperationDivide(entry);
			break;
		case OpKind::IsEqual:
		case OpKind::IsLessEqual:
		case OpKind::IsGreaterEqual:
		case OpKind::IsNotEqual:
		case OpKind::IsLess:
		case OpKind::IsGreater:
			OperationCompare(entry);
			break;
		case OpKind::Assign:
			OperationAssign(entry);
			break;
		case OpKind::Jump:
			OperationJump(entry, unresolvedJumps);
			break;
		case OpKind::IfFalseJump:
			OperationIfFalseJump(entry, unresolvedJumps);
			break;
		case OpKind::Print:
			OperationPrint(entry);
			break;
		case OpKind::Exit:
			_pGenProl16->Sleep();
			break;
		default:
			break;
		}
	}

	for (auto unresolvedJump : unresolvedJumps)
	{
		auto iterator = _tacEntries.cbegin();

		std::advance(iterator, unresolvedJump.second);

		_pGenProl16->SetAddress(unresolvedJump.first, (*iterator)->GetEntryAddress());		
	}

	_pGenProl16->WriteIex(os);
}

void CodeGenerator::OperationAdd(TACEntry* apTacEntry)
{
	int regA = _pRegisterAdmin->GetRegister(apTacEntry->GetLeftSymbol());
	int regB = _pRegisterAdmin->GetRegister(apTacEntry->GetRightSymbol());

	// regA contains result of addition -> assign to DAC-Entry
	_pGenProl16->Add(regA, regB);

	VarSymbol* resultSymbol = CastToVarSymbol(apTacEntry->GetResultSymbol());
	int regResult = _pRegisterAdmin->AssignRegister(apTacEntry->GetResultSymbol());

	_pGenProl16->Move(regResult, regA);
	SaveRegisterToMemory(resultSymbol->GetOffset(), regResult);

	_pRegisterAdmin->FreeRegister(regA);
	_pRegisterAdmin->FreeRegister(regB);
	_pRegisterAdmin->FreeRegister(regResult);
}

void CodeGenerator::OperationSubtract(TACEntry* apTacEntry)
{
	int regA = _pRegisterAdmin->GetRegister(apTacEntry->GetLeftSymbol());
	int regB = _pRegisterAdmin->GetRegister(apTacEntry->GetRightSymbol());

	// regA contains result of subtraction -> assign to DAC-Entry
	_pGenProl16->Sub(regA, regB);

	VarSymbol* resultSymbol = CastToVarSymbol(apTacEntry->GetResultSymbol());
	int regResult = _pRegisterAdmin->AssignRegister(apTacEntry->GetResultSymbol());

	_pGenProl16->Move(regResult, regA);
	SaveRegisterToMemory(resultSymbol->GetOffset(), regResult);

	_pRegisterAdmin->FreeRegister(regA);
	_pRegisterAdmin->FreeRegister(regB);
	_pRegisterAdmin->FreeRegister(regResult);
}

void CodeGenerator::OperationMultiply(TACEntry* apTacEntry)
{
	int regA = _pRegisterAdmin->GetRegister(apTacEntry->GetLeftSymbol()); // multiplicand
	int regB = _pRegisterAdmin->GetRegister(apTacEntry->GetRightSymbol()); // multiplier
	int regJmp = _pRegisterAdmin->GetRegister(); // used for jumps

	// regResult contains result of multiplication -> assign to DAC-Entry
	auto resultSymbol = CastToVarSymbol(apTacEntry->GetResultSymbol());
	int regResult = _pRegisterAdmin->AssignRegister(apTacEntry->GetResultSymbol()); // will contain result

	_pGenProl16->LoadI(regResult, 0); //init
	WORD codePosStart = _pGenProl16->GetCodePosition(); //start of loop begin
	int helpReg = _pRegisterAdmin->GetRegister();
	_pGenProl16->LoadI(helpReg, 0);
	_pGenProl16->Comp(regB, helpReg); //compare: multiplier != 0
	WORD jumpData1 = _pGenProl16->LoadI(regJmp, 0); //stores jump address of while-statement
	_pGenProl16->JumpZ(regJmp); //jump if zero bit is set (multiplier = 0)
	_pGenProl16->ShR(regB); //multiplier = mulitiplier >> 1

	WORD jumpData2 = _pGenProl16->LoadI(regJmp, 0); //stores jump address of if-statement

	//jump if carry bit is set ( multiplier = 3 -> 011 >> 1 = 001 (carry bit = 1) )
	_pGenProl16->JumpC(regJmp);
	_pGenProl16->ShL(regA); //multiplicand = multiplicand << 1
	_pGenProl16->LoadI(regJmp, codePosStart); //prepeare jump address
	_pGenProl16->Jump(regJmp); //jump to begin of while-statement
	//sets jump address for if-statement
	_pGenProl16->SetAddress(jumpData2, _pGenProl16->GetCodePosition());
	_pGenProl16->Add(regResult, regA); //adds multiplicand to result register

	_pGenProl16->ShL(regA); //multiplicand = multiplicand << 1
	_pGenProl16->LoadI(regJmp, codePosStart); //prepeare jump address
	_pGenProl16->Jump(regJmp); //jump to begin of while-statement

	//sets jump address for end of while-statement
	_pGenProl16->SetAddress(jumpData1, _pGenProl16->GetCodePosition());

	SaveRegisterToMemory(resultSymbol->GetOffset(), regResult);

	// free all other registers
	_pRegisterAdmin->FreeRegister(regA);
	_pRegisterAdmin->FreeRegister(regB);
	_pRegisterAdmin->FreeRegister(regJmp);
	_pRegisterAdmin->FreeRegister(helpReg);
	_pRegisterAdmin->FreeRegister(regResult);
}

void CodeGenerator::OperationDivide(TACEntry* apTacEntry)
{
	int regA = _pRegisterAdmin->GetRegister(apTacEntry->GetLeftSymbol()); // dividend
	int regB = _pRegisterAdmin->GetRegister(apTacEntry->GetRightSymbol()); // divisor
	int regJmp = _pRegisterAdmin->GetRegister(); // used for jumps
	int regRemainder = _pRegisterAdmin->GetRegister(); // remainder
	_pGenProl16->LoadI(regRemainder, 0);
	int regBits = _pRegisterAdmin->GetRegister(); // bit counter
	_pGenProl16->LoadI(regBits, 16);
	WORD codePosStart = _pGenProl16->GetCodePosition();
	_pGenProl16->ShL(regA);
	_pGenProl16->ShLC(regRemainder);
	WORD jumpData1 = _pGenProl16->LoadI(regJmp, 0);
	_pGenProl16->JumpC(regJmp);
	_pGenProl16->Comp(regB, regRemainder);
	_pGenProl16->JumpC(regJmp);
	_pGenProl16->JumpZ(regJmp);
	WORD jumpData2 = _pGenProl16->LoadI(regJmp, 0);
	_pGenProl16->Jump(regJmp);
	_pGenProl16->SetAddress(jumpData1, _pGenProl16->GetCodePosition());
	_pGenProl16->Sub(regRemainder, regB);
	int helpReg = _pRegisterAdmin->GetRegister();
	_pGenProl16->LoadI(helpReg, 1);
	_pGenProl16->Or(regA, helpReg);
	_pGenProl16->SetAddress(jumpData2, _pGenProl16->GetCodePosition());
	_pGenProl16->Dec(regBits);
	WORD jumpData3 = _pGenProl16->LoadI(regJmp, 0);
	_pGenProl16->JumpZ(regJmp);
	_pGenProl16->LoadI(regJmp, codePosStart);
	_pGenProl16->Jump(regJmp);
	_pGenProl16->SetAddress(jumpData3, _pGenProl16->GetCodePosition());

	auto resultSymbol = CastToVarSymbol(apTacEntry->GetResultSymbol());
	int regResult = _pRegisterAdmin->AssignRegister(apTacEntry->GetResultSymbol());

	// regA contains result of division -> assign to DAC-Entry
	_pGenProl16->Move(regResult, regA);

	SaveRegisterToMemory(resultSymbol->GetOffset(), regResult);

	// free all other registers
	_pRegisterAdmin->FreeRegister(regB);
	_pRegisterAdmin->FreeRegister(regA);
	_pRegisterAdmin->FreeRegister(regJmp);
	_pRegisterAdmin->FreeRegister(regRemainder);
	_pRegisterAdmin->FreeRegister(regBits);
	_pRegisterAdmin->FreeRegister(helpReg);
	_pRegisterAdmin->FreeRegister(regResult);
}

void CodeGenerator::OperationAssign(TACEntry* apTacEntry)
{
	VarSymbol* resultSymbol = CastToVarSymbol(apTacEntry->GetResultSymbol());

	auto regResult = _pRegisterAdmin->AssignRegister(resultSymbol);

	auto regA = _pRegisterAdmin->GetRegister(apTacEntry->GetLeftSymbol());

	_pGenProl16->Move(regResult, regA);

	SaveRegisterToMemory(resultSymbol->GetOffset(), regResult);

	_pRegisterAdmin->FreeRegister(regResult);
	_pRegisterAdmin->FreeRegister(regA);
}

void CodeGenerator::OperationJump(TACEntry* apTacEntry, TUnresolvedJumps& arUnresolvedJumps)
{
	auto leftSymbol = dynamic_cast<ConstIntSymbol*>(apTacEntry->GetLeftSymbol());

	int regJumpAddress = _pRegisterAdmin->GetRegister();
	auto jumpAddressData = _pGenProl16->LoadI(regJumpAddress, 0);

	arUnresolvedJumps.push_back(std::pair<WORD, const int>(jumpAddressData, leftSymbol->GetValue()));

	_pGenProl16->Jump(regJumpAddress);

	_pRegisterAdmin->FreeRegister(regJumpAddress);
}

void CodeGenerator::OperationIfFalseJump(TACEntry* apTacEntry, TUnresolvedJumps& arUnresolvedJumps)
{
	int regA = _pRegisterAdmin->GetRegister(apTacEntry->GetLeftSymbol());
	auto rightSymbol = dynamic_cast<ConstIntSymbol*>(apTacEntry->GetRightSymbol());

	int regJumpAddress = _pRegisterAdmin->GetRegister();
	auto jumpAddressData = _pGenProl16->LoadI(regJumpAddress, 0);

	arUnresolvedJumps.push_back(std::pair<WORD, const int>(jumpAddressData, rightSymbol->GetValue()));

	int regZero = _pRegisterAdmin->GetRegister();
	_pGenProl16->LoadI(regZero, 0);
	_pGenProl16->Add(regA, regZero);
	_pGenProl16->JumpZ(regJumpAddress);

	_pRegisterAdmin->FreeRegister(regA);
	_pRegisterAdmin->FreeRegister(regJumpAddress);
	_pRegisterAdmin->FreeRegister(regZero);
}

void CodeGenerator::OperationPrint(TACEntry* apTacEntry)
{
	int regA = _pRegisterAdmin->GetRegister(apTacEntry->GetLeftSymbol());

	_pGenProl16->PrintInt(regA);

	_pRegisterAdmin->FreeRegister(regA);
}

void CodeGenerator::OperationCompare(TACEntry* apTacEntry)
{
	int regA = _pRegisterAdmin->GetRegister(apTacEntry->GetLeftSymbol());
	int regB = _pRegisterAdmin->GetRegister(apTacEntry->GetRightSymbol());

	VarSymbol* resultSymbol = CastToVarSymbol(apTacEntry->GetResultSymbol());
	int regResult = _pRegisterAdmin->AssignRegister(resultSymbol);


	switch (apTacEntry->GetOperatorKind())
	{
	case OpKind::IsEqual:
		CompareEquals(apTacEntry, regResult, true);
		break;
	case OpKind::IsLessEqual:
		CompareLess(apTacEntry, regResult, false, true);
		break;
	case OpKind::IsGreaterEqual:
		CompareLess(apTacEntry, regResult, false, false);
		break;
	case OpKind::IsNotEqual:
		CompareEquals(apTacEntry, regResult, false);
		break;
	case OpKind::IsLess:
		CompareLess(apTacEntry, regResult, true, false);
		break;
	case OpKind::IsGreater:
		CompareLess(apTacEntry, regResult, true, true);
		break;
	}

	SaveRegisterToMemory(resultSymbol->GetOffset(), regResult);

	_pRegisterAdmin->FreeRegister(regA);
	_pRegisterAdmin->FreeRegister(regB);
	_pRegisterAdmin->FreeRegister(regResult);
}

VarSymbol* CodeGenerator::CastToVarSymbol(Symbol* symbol)
{
	VarSymbol* resultSymbol = dynamic_cast<VarSymbol*>(symbol);
	if (resultSymbol == nullptr)
	{
		throw std::exception("Result symbol must be a variable.");
	}
	return resultSymbol;
}

void CodeGenerator::SaveRegisterToMemory(int address, int regValue)
{
	auto regResultAddress = _pRegisterAdmin->GetRegister();

	_pGenProl16->LoadI(regResultAddress, address);
	_pGenProl16->Store(regValue, regResultAddress);

	_pRegisterAdmin->FreeRegister(regResultAddress);
}

void CodeGenerator::Compare(TACEntry* apTacEntry, bool inverseComparison)
{
	int regA = _pRegisterAdmin->GetRegister(apTacEntry->GetLeftSymbol());
	int regB = _pRegisterAdmin->GetRegister(apTacEntry->GetRightSymbol());

	if (inverseComparison)
	{
		_pGenProl16->Comp(regB, regA);
	}
	else
	{
		_pGenProl16->Comp(regA, regB);
	}


	_pRegisterAdmin->FreeRegister(regA);
	_pRegisterAdmin->FreeRegister(regB);
}

void CodeGenerator::CompareEquals(TACEntry* apTacEntry, int regResult, bool inverseResults)
{
	int regJumpAddress1 = _pRegisterAdmin->GetRegister();
	auto jumpAddressData1 = _pGenProl16->LoadI(regJumpAddress1, 0);

	Compare(apTacEntry, false);
	_pGenProl16->JumpZ(regJumpAddress1);

	// zero not set
	_pGenProl16->LoadI(regResult, inverseResults ? 0 : 1);

	int regJumpAddress2 = _pRegisterAdmin->GetRegister();
	auto jumpAddressData2 = _pGenProl16->LoadI(regJumpAddress2, 0);
	_pGenProl16->Jump(regJumpAddress2);
	_pGenProl16->SetAddress(jumpAddressData1, _pGenProl16->GetCodePosition());

	// zero set
	_pGenProl16->LoadI(regResult, inverseResults ? 1 : 0);
	_pGenProl16->SetAddress(jumpAddressData2, _pGenProl16->GetCodePosition());

	_pRegisterAdmin->FreeRegister(regJumpAddress1);
	_pRegisterAdmin->FreeRegister(regJumpAddress2);
}

void CodeGenerator::CompareLess(TACEntry* apTacEntry, int regResult, bool inverseResults, bool inverseComparison)
{
	int regJumpAddress1 = _pRegisterAdmin->GetRegister();
	auto jumpAddressData1 = _pGenProl16->LoadI(regJumpAddress1, 0);

	Compare(apTacEntry, inverseComparison);

	_pGenProl16->JumpC(regJumpAddress1);

	// carry set
	_pGenProl16->LoadI(regResult, inverseResults ? 0 : 1);

	int regJumpAddress2 = _pRegisterAdmin->GetRegister();
	auto jumpAddressData2 = _pGenProl16->LoadI(regJumpAddress2, 0);
	_pGenProl16->Jump(regJumpAddress2);
	_pGenProl16->SetAddress(jumpAddressData1, _pGenProl16->GetCodePosition());

	// carry not set
	_pGenProl16->LoadI(regResult, inverseResults ? 1 : 0);
	_pGenProl16->SetAddress(jumpAddressData2, _pGenProl16->GetCodePosition());

	_pRegisterAdmin->FreeRegister(regJumpAddress1);
	_pRegisterAdmin->FreeRegister(regJumpAddress2);
}