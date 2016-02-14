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

void TACGenerator::CleanEntries() 
{
	 for (TACEntry* pEntry : _tacEntries) 
	 {
		  delete pEntry;
		  pEntry = 0;
	 }
}

std::list<TACEntry*> TACGenerator::GetEntries()
{
	 return _tacEntries;
}

void TACGenerator::Print(std::ostream & ostream)
{
	 for (TACEntry* pEntry : _tacEntries)
	 {
		  pEntry->Print(ostream);
	 }
}

void TACGenerator::PrintEntries(std::ostream & ostream)
{
	int i = 0;

	for (TACEntry* pEntry : _tacEntries)
	{
		ostream << i << ": ";
		pEntry->PrintEntry(ostream);
		i++;
	}
}