#include "SymbolFactory.h"

SymbolFactory::SymbolFactory()
{}

ConstIntSymbol * SymbolFactory::CreateConstIntSymbol(std::string const & name, Type * type, int value)
{
	return new ConstIntSymbol(name, type, value);
}

TypeSymbol * SymbolFactory::CreateTypeSymbol(std::string const & name, Type * type)
{
	return new TypeSymbol(name, type);
}

VarSymbol * SymbolFactory::CreateVarSymbol(std::string const & name, Type * type, size_t offset)
{
	return new VarSymbol(name, type, offset);
}
