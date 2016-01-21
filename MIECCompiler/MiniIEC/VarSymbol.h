#ifndef VARSYMBOL_H
#define VARSYMBOL_H

#include "Symbol.h"

class VarSymbol : public Symbol
{
public:
	VarSymbol(std::string const& name, Type* type, size_t offset);

	size_t GetOffset();

	void Print(std::ostream& ostream);
private:
	size_t _offset;
};

#endif