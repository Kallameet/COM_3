#include "SymbolTable.h"

void SymbolTable::Add(Symbol * symbol)
{
	_symbols[symbol->GetName()] = symbol;
}

Symbol * SymbolTable::Find(std::string const & name)
{
	return _symbols[name];
}

void SymbolTable::Print(std::ostream & ostream)
{
#ifdef _DEBUG 

	ostream << "Class: SymbolTable" << std::endl << std::endl;
	for (auto sym : _symbols)
	{
		sym.second->Print(ostream);
		ostream << std::endl;
	}

#endif
}

SymbolTable::~SymbolTable()
{
	for (auto symbol : _symbols)
	{
		delete symbol.second;
	}
}