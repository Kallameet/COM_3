#include "TACGenerator.h"

void TACGenerator::AddEntry(OpKind operatorKind, Symbol* leftSymbol) 
{
	 TACEntry* tacEntry = new TACEntry(operatorKind, leftSymbol);
	 _tacEntries.push_back(tacEntry);
}

void TACGenerator::AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* rightSymbol)
{
	 TACEntry* tacEntry = new TACEntry(operatorKind, leftSymbol, rightSymbol);
	 _tacEntries.push_back(tacEntry);
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
	 for (TACEntry* pEntry : _tacEntries)
	 {
		  pEntry->Print(ostream);
	 }
}
