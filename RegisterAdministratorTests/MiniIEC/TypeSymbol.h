#ifndef TYPESYMBOL_H
#define TYPESYMBOL_H

#include "Symbol.h"

class TypeSymbol : public Symbol
{
public:
	TypeSymbol(std::string const& name, Type* type);

	void Print(std::ostream& ostream);
};

#endif