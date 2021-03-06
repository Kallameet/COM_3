#include "TACEntry.h"

TACEntry::TACEntry(OpKind operatorKind, Symbol * leftSymbol, Symbol* resultSymbol)
	: _operatorKind(operatorKind), _leftSymbol(leftSymbol), _resultSymbol(resultSymbol)
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

void TACEntry::SetTmpResult(int reg)
{
	 // TODO
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
	
	ostream << "Class: TACEntry" << std::endl;
	ostream << "Operator kind:" << mappedEnumNames[_operatorKind] << std::endl;
	ostream << "Left symbol:" << std::endl;
	_leftSymbol->Print(ostream);
	ostream << "Right symbol:" << std::endl;
	_rightSymbol->Print(ostream);
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

	if (_rightSymbol != nullptr)
	{
		ostream << " " << _rightSymbol->GetName();
	}
		
	ostream << std::endl;
	
}