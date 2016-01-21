#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include "Object.h"
#include "Symbol.h"

typedef std::unordered_map<std::string, Symbol*> SymbolMap;

class SymbolTable : public Object
{
public:
	void Add(Symbol* symbol);

	Symbol* Find(std::string const& name);

	void Print(std::ostream & ostream);
private:
	SymbolMap _symbols;
};

#endif