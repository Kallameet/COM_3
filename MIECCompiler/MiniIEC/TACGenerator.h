#ifndef TACGENERATOR_H
#define TACGENERATOR_H

#include "Object.h"
#include "TACEntry.h"

class TACGenerator : public Object
{
public:
	TACEntry* AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* resultSymbol);
	TACEntry* AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* rightSymbol, Symbol* resultSymbol);
	std::list<TACEntry*> GetEntries();
	size_t GetLastElementIndex();
	void CleanEntries();
	virtual void Print(std::ostream& ostream);

	virtual ~TACGenerator();
private:
	std::list<TACEntry*> _tacEntries;
};

#endif