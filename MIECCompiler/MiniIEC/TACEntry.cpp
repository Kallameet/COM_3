#include "TACEntry.h"

TACEntry::TACEntry(OpKind operatorKind, Symbol * leftSymbol, Symbol* resultSymbol)
	: _operatorKind(operatorKind), _leftSymbol(leftSymbol), _rightSymbol(nullptr), _resultSymbol(resultSymbol)
{}

TACEntry::TACEntry(OpKind operatorKind, Symbol * leftSymbol, Symbol * rightSymbol, Symbol* resultSymbol)
	: _operatorKind(operatorKind), _leftSymbol(leftSymbol), _rightSymbol(rightSymbol), _resultSymbol(resultSymbol)
{}

Symbol* TACEntry::GetLeftSymbol()
{
	return _leftSymbol;
}

Symbol* TACEntry::GetRightSymbol()
{
	return _rightSymbol;
}

Symbol* TACEntry::GetResultSymbol()
{
	return _resultSymbol;
}

void TACEntry::SetLeftSymbol(Symbol* symbol)
{
	_leftSymbol = symbol;
}

void TACEntry::SetRightSymbol(Symbol* symbol)
{
	_rightSymbol = symbol;
}

void TACEntry::SetResultSymbol(Symbol* symbol)
{
	_resultSymbol = symbol;
}

OpKind TACEntry::GetOperatorKind()
{
	return _operatorKind;
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
#ifdef _DEBUG 

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

#endif
}

TACEntry::~TACEntry()
{}