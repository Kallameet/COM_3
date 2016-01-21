#ifndef SYMBOLFACTORY_H
#define SYMBOLFACTORY_H

#include "Object.h"
#include "ConstIntSymbol.h"
#include "TypeSymbol.h"
#include "VarSymbol.h"

class SymbolFactory : public Object
{
public:
	SymbolFactory();

	ConstIntSymbol* CreateConstIntSymbol(std::string const& name, Type* type, int value);
	TypeSymbol* CreateTypeSymbol(std::string const& name, Type* type);
	VarSymbol* CreateVarSymbol(std::string const& name, Type* type, size_t offset);
private:

};

#endif