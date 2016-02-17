#ifndef SYMBOLFACTORY_H
#define SYMBOLFACTORY_H

#include "Object.h"
#include "ConstIntSymbol.h"
#include "TypeSymbol.h"
#include "VarSymbol.h"

class SymbolFactory : public Object
{
public:
	 /**
	 * <summary>  Constructor. </summary>
	 */
	 SymbolFactory();

	 /**
	 * <summary>  Create a constintsymbol. </summary>
	 *
	 * <param name="name">  The name of the constintsymbol. </param>
	 * <param name="type">  The type of the constintsymbol. </param>
	 * <param name="value">  The value of the constintsymbol. </param>
	 *
	 * <returns>  Pointer to constintsymbol.
	 */
	 ConstIntSymbol* CreateConstIntSymbol(std::string const& name, Type* type, int value);

	 /**
	 * <summary>  Create a typesymbol. </summary>
	 *
	 * <param name="name">  The name of the typesymbol. </param>
	 * <param name="type">  The type of the typesymbol. </param>
	 *
	 * <returns>  Pointer to typesymbol.
	 */
	 TypeSymbol* CreateTypeSymbol(std::string const& name, Type* type);

	 /**
	 * <summary>  Create a varsymbol. </summary>
	 *
	 * <param name="name">  The name of the varsymbol. </param>
	 * <param name="type">  The type of the varsymbol. </param>
	 * <param name="offset">  The offset of the varsymbol. </param>
	 *
	 * <returns>  Pointer to varsymbol.
	 */
	 VarSymbol* CreateVarSymbol(std::string const& name, Type* type, size_t offset);

private:

};

#endif