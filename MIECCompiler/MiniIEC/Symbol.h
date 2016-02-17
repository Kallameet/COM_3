#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <iostream>
#include "Object.h"
#include "Type.h"

class Symbol : public Object
{
public:
	 /**
	 * <summary>  Constructor. </summary>
	 *
	 * <param name="name">   The name of the symbol. </param>
	 * <param name="type">	 The type of the symbol. </param>
	 */
	 Symbol(std::string const& name, Type* type);

	 /**
	 * <summary>  Get name of the symbol. </summary>
	 *
	 * <returns> Name of symbol.
	 */
	 std::string GetName();

	 /**
	 * <summary>  Get type of the symbol. </summary>
	 *
	 * <returns> Type of symbol.
	 */
	 Type* GetType();

	 /**
	 * <summary>  Prints the symbol to given ostream. </summary>
	 *
	 * <param name="ostream">   Ostream where symbol is printed to. </param>
	 */
	 virtual void Print(std::ostream& ostream);

private:
	 std::string _name;
	 Type* _type;
};

#endif