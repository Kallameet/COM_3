#include "TACEntry.h"

TACEntry::TACEntry(OpKind operatorKind, Symbol * leftSymbol, Symbol* resultSymbol)
	: _operatorKind(operatorKind), _leftSymbol(leftSymbol), _rightSymbol(nullptr), _resultSymbol(resultSymbol)
{}

TACEntry::TACEntry(OpKind operatorKind, Symbol * leftSymbol, Symbol * rightSymbol, Symbol* resultSymbol)
	: _operatorKind(operatorKind), _leftSymbol(leftSymbol), _rightSymbol(rightSymbol), _resultSymbol(resultSymbol)
{}

TACEntry* TACEntry::GetArg1()
{
	 // TODO
	 return nullptr;
}

TACEntry* TACEntry::GetArg2()
{
	 // TODO
	 return nullptr;
}

OpKind TACEntry::GetOperatorKind()
{
	 return _operatorKind;
}

void TACEntry::SetTmpResult(int reg)
{
	 _tmpResult = reg;
}

int TACEntry::GetTmpResult()
{
	 return _tmpResult;
}

void TACEntry::SetEntryAddress(WORD address) 
{
	 _address = address;
}

WORD TACEntry::GetEntryAddress()
{
	 return _address;
}

void TACEntry::Print(std::ostream & ostream)
{
	std::unordered_map<OpKind, std::string> mappedEnumNames =
	{
		{ OpKind::Add			, "Add" },
		{ OpKind::Subtract		, "Substract" },
		{ OpKind::Multiply		, "Multiply" },
		{ OpKind::Divide		, "Divide" },
		{ OpKind::IsEqual		, "IsEqual" },
		{ OpKind::IsLessEqual	, "IsLessEqual" },
		{ OpKind::IsGreaterEqual, "IsGreaterEqual" },
		{ OpKind::IsNotEqual	, "IsNotEqual" },
		{ OpKind::IsLess		, "IsLess" },
		{ OpKind::IsGreater		, "IsGreater" },
		{ OpKind::Assign		, "Assign" },
		{ OpKind::Jump			, "Jump" },
		{ OpKind::IfJump		, "IfJump" },
		{ OpKind::IfFalseJump	, "IfFalseJump" },
		{ OpKind::Print			, "Print" },
		{ OpKind::Exit			, "Exit" }
	};
		
	if (_resultSymbol != nullptr)
	{
		ostream << _resultSymbol->GetName() << " = ";
	}

	ostream << mappedEnumNames[_operatorKind] << "( ";
	
	if (_leftSymbol != nullptr)
	{
		ostream << _leftSymbol->GetName() << " ";
	}

	if (_rightSymbol != nullptr)
	{
		ostream << _rightSymbol->GetName() << " ";		
	}

	ostream << ")";
}

void TACEntry::PrintEntry(std::ostream & ostream)
{
	std::unordered_map<OpKind, std::string> mappedEnumNames =
	{
		{ OpKind::Add			, "Add" },
		{ OpKind::Subtract		, "Substract" },
		{ OpKind::Multiply		, "Multiply" },
		{ OpKind::Divide		, "Divide" },
		{ OpKind::IsEqual		, "IsEqual" },
		{ OpKind::IsLessEqual	, "IsLessEqual" },
		{ OpKind::IsGreaterEqual, "IsGreaterEqual" },
		{ OpKind::IsNotEqual	, "IsNotEqual" },
		{ OpKind::IsLess		, "IsLess" },
		{ OpKind::IsGreater		, "IsGreater" },
		{ OpKind::Assign		, "Assign" },
		{ OpKind::Jump			, "Jump" },
		{ OpKind::IfJump		, "IfJump" },
		{ OpKind::IfFalseJump	, "IfFalseJump" },
		{ OpKind::Print			, "Print" },
		{ OpKind::Exit			, "Exit" }
	};

	
	ostream << _leftSymbol->GetName() << " " << mappedEnumNames[_operatorKind];

	if (_leftSymbol != nullptr)
	{
		ostream << " " << _rightSymbol->GetName();
	}

	if (_rightSymbol != nullptr)
	{
		ostream << " " << _rightSymbol->GetName();
	}
		
	ostream << std::endl;
	
}