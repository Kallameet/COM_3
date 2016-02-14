#ifndef TACGENERATOR_H
#define TACGENERATOR_H

#include "Object.h"
#include "TACEntry.h"

class TACGenerator : public Object
{
public:
	void AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* resultSymbol);
	 void AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* rightSymbol, Symbol* resultSymbol);
	 std::list<TACEntry*> GetEntries();
	 void CleanEntries();
	 virtual void Print(std::ostream& ostream);
	 
private:
	 std::list<TACEntry*> _tacEntries;
};

#endif