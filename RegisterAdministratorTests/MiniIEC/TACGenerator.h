#ifndef TACGENERATOR_H
#define TACGENERATOR_H

#include "Object.h"
#include "TACEntry.h"

class TACGenerator : public Object
{
public:
	 void AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* resultSymbol);
	 void AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* rightSymbol, Symbol* resultSymbol);
	 void CleanEntries();
	 std::list<TACEntry*> GetEntries();
	 virtual void Print(std::ostream& ostream);
	 virtual void PrintEntries(std::ostream& ostream);
private:
	 std::list<TACEntry*> _tacEntries;
};

#endif