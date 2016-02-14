#ifndef CONSTINTSYMBOL_H
#define CONSTINTSYMBOL_H

#include "Symbol.h"

class ConstIntSymbol : public Symbol
{
public:
	ConstIntSymbol(std::string const& name, Type* type, int value);

	int GetValue();

	void Print(std::ostream& ostream);
private:
	int _value;
};

#endif