#ifndef CONSTINTSYMBOL_H
#define CONSTINTSYMBOL_H

#include "Symbol.h"

class ConstIntSymbol : public Symbol
{
public:
	 /**
	 * <summary>  Constructor. </summary>
	 *
	 * <param name="name">   The name of the constintsymbol. </param>
	 * <param name="type">	 The type of the constintsymbol. </param>
	 * <param name="value">	 The value of the constintsymbol. </param>
	 */
	 ConstIntSymbol(std::string const& name, Type* type, int value);

	 /**
	 * <summary>  Get offset of the constintsymbol. </summary>
	 *
	 * <returns> Value of constintsymbol. </returns>
	 */
	 int GetValue();

	 /**
	 * <summary>  Prints the constintsymbol to given ostream. </summary>
	 *
	 * <param name="ostream">   Ostream where constintsymbol is printed to. </param>
	 */
	 void Print(std::ostream& ostream);

private:
	 int _value;
};

#endif