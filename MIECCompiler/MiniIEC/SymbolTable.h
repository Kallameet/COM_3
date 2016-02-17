#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include "Object.h"
#include "Symbol.h"

using SymbolMap = std::unordered_map<std::string, Symbol*>;

class SymbolTable : public Object
{
public:
	 /**
	 * <summary>  Add a symbol to the symboltable. </summary>
	 *
	 * <param name="symbol">  The symbol that is added. </param>
	 */
	 void Add(Symbol* symbol);

	 /**
	 * <summary>  Find a symbol in the symboltable. </summary>
	 *
	 * <param name="name">  The name of the symbol. </param>
	 *
	 * <returns> Pointer to the symbol that was found. </returns>
	 */
	 Symbol* Find(std::string const& name);

	 /**
	 * <summary>  Prints all symbols in the symboltable to given ostream. </summary>
	 *
	 * <param name="ostream">   Ostream where symbols are printed to. </param>
	 */
	 void Print(std::ostream & ostream);

	 /**
	 * <summary>  Destructor. </summary>
	 *
	 */
	 virtual ~SymbolTable();

private:
	 SymbolMap _symbols;
};

#endif