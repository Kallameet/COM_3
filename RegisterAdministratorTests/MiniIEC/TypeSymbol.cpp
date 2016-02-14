#include "TypeSymbol.h"

TypeSymbol::TypeSymbol(std::string const & name, Type * type) : Symbol(name, type)
{}

void TypeSymbol::Print(std::ostream & ostream)
{
	ostream << "Class: TypeSymbol" << std::endl;
	Symbol::Print(ostream);
}
