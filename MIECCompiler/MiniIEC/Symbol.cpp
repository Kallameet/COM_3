#include "Symbol.h"

Symbol::Symbol(std::string const& name, Type * type) : _name(name), _type(type)
{}

std::string Symbol::GetName()
{
	return _name;
}

Type * Symbol::GetType()
{
	return _type;
}

void Symbol::Print(std::ostream & ostream)
{
#ifdef _DEBUG 

	ostream << "Class: Symbol" << std::endl;
	ostream << "Name: " << _name << std::endl;
	ostream << "Type: " << _type->GetTypeName() << std::endl;

#endif
}
