#ifndef TYPESYMBOL_H
#define TYPESYMBOL_H

#include "Symbol.h"

class TypeSymbol : public Symbol
{
public:
	 /**
	 * <summary>  Constructor. </summary>
	 *
	 * <param name="name">   The name of the typesymbol. </param>
	 * <param name="type">	 The type of the typesymbol. </param>
	 */
	 TypeSymbol(std::string const& name, Type* type);
	 /**
	 * <summary>  Prints the typesymbol to given ostream. </summary>
	 *
	 * <param name="ostream">   Ostream where typesymbol is printed to. </param>
	 */
	 void Print(std::ostream& ostream);
};

#endif