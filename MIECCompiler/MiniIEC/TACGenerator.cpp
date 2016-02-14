#include "TACGenerator.h"

void TACGenerator::AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* resultSymbol)
{
	 TACEntry* tacEntry = new TACEntry(operatorKind, leftSymbol, resultSymbol);
	 _tacEntries.push_back(tacEntry);	 
}

void TACGenerator::AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* rightSymbol, Symbol* resultSymbol)
{
	TACEntry* tacEntry = new TACEntry(operatorKind, leftSymbol, rightSymbol, resultSymbol);
	 _tacEntries.push_back(tacEntry);	 
}

std::list<TACEntry*> TACGenerator::GetEntries()
{
	return _tacEntries;
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
	size_t counter = 0;

	 for (TACEntry* pEntry : _tacEntries)
	 {
		 ostream << counter << ": ";
		 pEntry->Print(ostream);
		 ostream << std::endl;
		 counter++;
	 }
}
