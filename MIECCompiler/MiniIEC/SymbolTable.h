#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include "Object.h"
#include "Symbol.h"

using SymbolMap = std::unordered_map<std::string, Symbol*>;

class SymbolTable : public Object
{
public:
	void Add(Symbol* symbol);
	Symbol* Find(std::string const& name);
	void Print(std::ostream & ostream);

	virtual ~SymbolTable();
private:
	SymbolMap _symbols;
};

#endif