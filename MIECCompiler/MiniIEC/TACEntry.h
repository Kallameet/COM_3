#ifndef TACENTRY_H
#define TACENTRY_H

#include "Object.h"
#include "OpKind.h"
#include "Symbol.h"

class TACEntry : public Object
{
public:
	TACEntry(OpKind operatorKind, Symbol* leftSymbol);
	TACEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* rightSymbol);

	virtual void Print(std::ostream& ostream);
private:
	OpKind _operatorKind;

	Symbol* _leftSymbol;
	Symbol* _rightSymbol;	
};

#endif