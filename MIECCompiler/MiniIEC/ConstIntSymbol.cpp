#include "ConstIntSymbol.h"

ConstIntSymbol::ConstIntSymbol(std::string const& name, Type * type, int value) : _value(value), Symbol(name, type)
{}

int ConstIntSymbol::GetValue()
{
	return _value;
}

void ConstIntSymbol::Print(std::ostream & ostream)
{
#ifdef _DEBUG 

	ostream << "Class: ConstIntSymbol" << std::endl;
	ostream << "Value: " << _value << std::endl;
	Symbol::Print(ostream);

#endif
}