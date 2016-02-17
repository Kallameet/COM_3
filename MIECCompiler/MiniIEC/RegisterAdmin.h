#ifndef REGISTERADMIN_H
#define REGISTERADMIN_H

#include "Object.h"
#include "TACEntry.h"
#include "CodeGenProl16\CodeGenProl16.h"

struct TRegister
{
	 Symbol* pSymbol;
	 bool free;
};

class RegisterAdmin : public Object
{
public:
	 /**
	 * <summary>  Constructor. </summary>
	 *
	 * <param name="pGenProl16">   The code generator which is needed for the registers. </param>
	 */
	 RegisterAdmin(MIEC::CodeGenProl16* pGenProl16);

	 /**
	 * <summary>  Get register without parameter. </summary>
	 *
	 * <returns> Number of register. </returns>
	 */
	 int GetRegister();

	 /**
	 * <summary>  Get register for a specific symbol. </summary>
	 *
	 * <param name="symbol">  Specific symbol.  </param>
	 *
	 * <returns> Number of register. </returns>
	 */
	 int GetRegister(Symbol* symbol);

	 /**
	 * <summary>  Assign register to a specific symbol. </summary>
	 *
	 * <param name="symbol">   Specific symbol. </param>
	 *
	 * <returns> Number of register. </returns>
	 */
	 int AssignRegister(Symbol* symbol);

	 /**
	 * <summary>  Free register with given register number. </summary>
	 *
	 * <param name="regNum">   Register number. </param>
	 */
	 void FreeRegister(int regNum);

private:
	 int FindSymbolInRegisters(Symbol * symbol);

	 MIEC::CodeGenProl16* _pGenProl16;

	 static size_t const _maxRegNum = 8;
	 TRegister _registers[_maxRegNum];
};

#endif