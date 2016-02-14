#ifndef TACENTRY_H
#define TACENTRY_H

#include "Object.h"
#include "OpKind.h"
#include "Symbol.h"

class TACEntry : public Object
{
public:
	TACEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* resultSymbol);
	TACEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* rightSymbol, Symbol* resultSymbol);
	TACEntry* GetArg1();
	TACEntry* GetArg2();
	void SetTmpResult(int reg);

	virtual void Print(std::ostream& ostream);
	virtual void PrintEntry(std::ostream& ostream);
	
private:
	OpKind _operatorKind;

	Symbol* _leftSymbol;
	Symbol* _rightSymbol;
	Symbol* _resultSymbol;
};

#endif