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
	
	void SetLeftSymbol(Symbol* symbol);
	void SetRightSymbol(Symbol* symbol);
	void SetResultSymbol(Symbol* symbol);

	virtual void Print(std::ostream& ostream);	
	
	virtual ~TACEntry();

private:
	OpKind _operatorKind;

	Symbol* _leftSymbol;
	Symbol* _rightSymbol;
	Symbol* _resultSymbol;
};

#endif