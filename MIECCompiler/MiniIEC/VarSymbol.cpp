#include "VarSymbol.h"

VarSymbol::VarSymbol(std::string const& name, Type * type, size_t offset) : _offset(offset), Symbol(name, type)
{}

size_t VarSymbol::GetOffset()
{
	return _offset;
}

void VarSymbol::Print(std::ostream & ostream)
{
#ifdef _DEBUG 

	ostream << "Class: VarSymbol" << std::endl;
	ostream << "Offset: " << _offset << std::endl;
	Symbol::Print(ostream);

#endif
}
