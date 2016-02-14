#include "TACGenerator.h"

TACEntry* TACGenerator::AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* resultSymbol)
{
	 TACEntry* tacEntry = new TACEntry(operatorKind, leftSymbol, resultSymbol);
	 _tacEntries.push_back(tacEntry);
	 return tacEntry;
}

TACEntry* TACGenerator::AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* rightSymbol, Symbol* resultSymbol)
{
	TACEntry* tacEntry = new TACEntry(operatorKind, leftSymbol, rightSymbol, resultSymbol);
	 _tacEntries.push_back(tacEntry);	
	 return tacEntry;
}

std::list<TACEntry*> TACGenerator::GetEntries()
{
	return _tacEntries;
}

size_t TACGenerator::GetLastElementIndex()
{
	return _tacEntries.size() - 1;
}

void TACGenerator::CleanEntries() 
{
	 for (TACEntry* pEntry : _tacEntries) 
	 {
		  delete pEntry;
		  pEntry = 0;
	 }
}

void TACGenerator::Print(std::ostream & ostream)
{
#ifdef _DEBUG 

	size_t counter = 0;

	 for (TACEntry* pEntry : _tacEntries)
	 {
		 ostream << counter << ": ";
		 pEntry->Print(ostream);
		 ostream << std::endl;
		 counter++;
	 }

#endif
}

TACGenerator::~TACGenerator()
{
	for (auto entry : _tacEntries)
	{
		delete entry;
	}
}