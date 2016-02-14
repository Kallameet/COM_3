#include "CodeGenerator.h"
#include "VarSymbol.h"

CodeGenerator::CodeGenerator(std::list<TACEntry*> entries) {
	 _pGenProl16 = new MIEC::CodeGenProl16;
	 _pRegAdmin = new RegisterAdmin(_pGenProl16);
	 for (TACEntry* entry : entries) {
		  _tacEntries.push_back(entry);
	 }
}

CodeGenerator::~CodeGenerator()
{
	 delete _pGenProl16;
	 delete _pRegAdmin;
}

void CodeGenerator::GenerateCode(std::ostream& os)
{
	 TUnresolvedJumps unrJumps;
	 for (TACEntry* entry : _tacEntries)
	 {
		  entry->SetEntryAddress(_pGenProl16->GetCodePosition());
		  OpKind operatorKind = entry->GetOperatorKind();
		  switch (operatorKind) {
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
				OperationCompare(entry);
				break;
		  case OpKind::IsLessEqual:
				OperationCompare(entry);
				break;
		  case OpKind::IsGreaterEqual:
				OperationCompare(entry);
				break;
		  case OpKind::IsNotEqual:
				OperationCompare(entry);
				break;
		  case OpKind::IsLess:
				OperationCompare(entry);
				break;
		  case OpKind::IsGreater:
				OperationCompare(entry);
				break;
		  case OpKind::Assign:
				OperationAssign(entry);
				break;
		  case OpKind::Jump:
				OperationJump(entry, unrJumps);
				break;
		  case OpKind::IfJump:
				OperationConditionalJump(entry, unrJumps);
				break;
		  case OpKind::IfFalseJump:
				OperationConditionalJump(entry, unrJumps);
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
}

void CodeGenerator::OperationAdd(TACEntry* apTacEntry)
{
	 int regA = _pRegAdmin->GetRegister(apTacEntry->GetArg1());
	 int regB = _pRegAdmin->GetRegister(apTacEntry->GetArg2());
	 _pGenProl16->Add(regA, regB);
	 // regA contains result of addition -> assign to DAC-Entry
	 int regResult = _pRegAdmin->AssignRegister(apTacEntry);
	 _pGenProl16->Move(regResult, regA);
	 apTacEntry->SetTmpResult(regResult);
	 _pRegAdmin->FreeRegister(regA);
	 _pRegAdmin->FreeRegister(regB);
}

void CodeGenerator::OperationSubtract(TACEntry* apTacEntry)
{
	 int regA = _pRegAdmin->GetRegister(apTacEntry->GetArg1());
	 int regB = _pRegAdmin->GetRegister(apTacEntry->GetArg2());
	 _pGenProl16->Sub(regA, regB);
	 // regA contains result of subtraction -> assign to DAC-Entry
	 int regResult = _pRegAdmin->AssignRegister(apTacEntry);
	 _pGenProl16->Move(regResult, regA);
	 apTacEntry->SetTmpResult(regResult);
	 _pRegAdmin->FreeRegister(regA);
	 _pRegAdmin->FreeRegister(regB);
}

void CodeGenerator::OperationMultiply(TACEntry* apTacEntry)
{
	 int regA = _pRegAdmin->GetRegister(apTacEntry->GetArg1()); // multiplicand
	 int regB = _pRegAdmin->GetRegister(apTacEntry->GetArg2()); // multiplier
	 int regJmp = _pRegAdmin->GetRegister(); // used for jumps
	 // regResult contains result of multiplication -> assign to DAC-Entry
	 int regResult = _pRegAdmin->AssignRegister(apTacEntry); // will contain result
	 _pGenProl16->LoadI(regResult, 0); //init
	 WORD codePosStart = _pGenProl16->GetCodePosition(); //start of loop begin
	 int helpReg = _pRegAdmin->GetRegister();
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

	 // free all other registers
	 _pRegAdmin->FreeRegister(regA);
	 _pRegAdmin->FreeRegister(regB);
	 _pRegAdmin->FreeRegister(regJmp);
	 _pRegAdmin->FreeRegister(helpReg);
}

void CodeGenerator::OperationDivide(TACEntry* apTacEntry)
{
	 int regA = _pRegAdmin->GetRegister(apTacEntry->GetArg1()); // dividend
	 int regB = _pRegAdmin->GetRegister(apTacEntry->GetArg2()); // divisor
	 int regJmp = _pRegAdmin->GetRegister(); // used for jumps
	 int regRemainder = _pRegAdmin->GetRegister(); // remainder
	 _pGenProl16->LoadI(regRemainder, 0);
	 int regBits = _pRegAdmin->GetRegister(); // bit counter
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
	 int helpReg = _pRegAdmin->GetRegister();
	 _pGenProl16->LoadI(helpReg, 1);
	 _pGenProl16->Or(regA, helpReg);
	 _pGenProl16->SetAddress(jumpData2, _pGenProl16->GetCodePosition());
	 _pGenProl16->Dec(regBits);
	 WORD jumpData3 = _pGenProl16->LoadI(regJmp, 0);
	 _pGenProl16->JumpZ(regJmp);
	 _pGenProl16->LoadI(regJmp, codePosStart);
	 _pGenProl16->Jump(regJmp);
	 _pGenProl16->SetAddress(jumpData3, _pGenProl16->GetCodePosition());

	 // regA contains result of division -> assign to DAC-Entry
	 int regResult = _pRegAdmin->AssignRegister(apTacEntry);
	 _pGenProl16->Move(regResult, regA);
	 apTacEntry->SetTmpResult(regResult);

	 // free all other registers
	 _pRegAdmin->FreeRegister(regB);
	 _pRegAdmin->FreeRegister(regA);
	 _pRegAdmin->FreeRegister(regJmp);
	 _pRegAdmin->FreeRegister(regRemainder);
	 _pRegAdmin->FreeRegister(regBits);
	 _pRegAdmin->FreeRegister(helpReg);
}

void CodeGenerator::OperationAssign(TACEntry* apTacEntry)
{
	 if (VarSymbol* arg1 = dynamic_cast<VarSymbol*>(apTacEntry->GetArg1()))
	 {
	 throw std::string("arg1 must be a variable");
	 }
	
	 else
	 {
		 //_pGenProl16->LoadI()
	 }
}

void CodeGenerator::OperationJump(TACEntry* apTacEntry, TUnresolvedJumps& arUnresolvedJumps)
{

}

void CodeGenerator::OperationConditionalJump(TACEntry* apTacEntry, TUnresolvedJumps& arUnresolvedJumps)
{

}

void CodeGenerator::OperationPrint(TACEntry* apTacEntry)
{
	
}

void CodeGenerator::OperationCompare(TACEntry* apTacEntry)
{
	 int regA = _pRegAdmin->GetRegister(apTacEntry->GetArg1());
	 int regB = _pRegAdmin->GetRegister(apTacEntry->GetArg2());
	 _pGenProl16->Comp(regA, regB);
	 _pRegAdmin->FreeRegister(regA);
	 _pRegAdmin->FreeRegister(regB);
}
