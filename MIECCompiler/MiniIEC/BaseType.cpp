#include <stdexcept>
#include "BaseType.h"

BaseType::BaseType(BaseTypeName typeName) : _typeName(typeName), Type(ResolveTypeToSize(typeName))
{}

std::string BaseType::GetTypeName() const
{
	switch (_typeName)
	{
	case BaseTypeName::INT:
		return "Integer";
		break;
	case BaseTypeName::FLOAT:
		return "Float";
		break;
	case BaseTypeName::CHAR:
		return "Char";
		break;	
	}
}

size_t BaseType::ResolveTypeToSize(BaseTypeName typeName)
{
	switch (typeName)
	{
	case BaseTypeName::INT:
		return 4;
		break;
	case BaseTypeName::FLOAT:
		return 4;
		break;
	case BaseTypeName::CHAR:
		return 1;
		break;
	default:
		throw std::invalid_argument("ResolveTypeToSize needs a valid BaseTypeName");
		break;
	}
}
