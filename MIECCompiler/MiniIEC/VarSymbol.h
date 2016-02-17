#ifndef VARSYMBOL_H
#define VARSYMBOL_H

#include "Symbol.h"

class VarSymbol : public Symbol
{
public:
	 /**
	 * <summary>  Constructor. </summary>
	 *
	 * <param name="name">   The name of the varsymbol. </param>
	 * <param name="type">	 The type of the varsymbol. </param>
	 * <param name="offset">	 The offset of the varsymbol. </param>
	 */
	 VarSymbol(std::string const& name, Type* type, size_t offset);

	 /**
	 * <summary>  Get offset of the varsymbol. </summary>
	 *
	 * <returns> Offset of varsymbol.
	 */
	 size_t GetOffset();

	 /**
	 * <summary>  Prints the varsymbol to given ostream. </summary>
	 *
	 * <param name="ostream">   Ostream where varsymbol is printed to. </param>
	 */
	 void Print(std::ostream& ostream);

private:
	 size_t _offset;
};

#endif