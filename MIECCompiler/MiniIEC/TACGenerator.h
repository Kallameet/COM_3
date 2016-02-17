#ifndef TACGENERATOR_H
#define TACGENERATOR_H

#include "Object.h"
#include "TACEntry.h"

class TACGenerator : public Object
{
public:
	/**
	* <summary> Creates a TACEntry and adds it to the internal list. </summary>
	*
	* <param name="operatorKind"> The operator of the TACEntry that will be created. </param>
	* <param name="leftSymbol"> The left symbol of the TACEntry that will be created. </param>
	* <param name="resultSymbol"> The result symbol of the TACEntry that will be created. </param>
	*
	* <returns> Returns a pointer to the added TACEntry. </returns>
	*/
	TACEntry* AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* resultSymbol);

	/**
	* <summary> Creates a TACEntry and adds it to the internal list. </summary>
	*
	* <param name="operatorKind"> The operator of the TACEntry that will be created. </param>
	* <param name="leftSymbol"> The left symbol of the TACEntry that will be created. </param>
	* <param name="resultSymbol"> The result symbol of the TACEntry that will be created. </param>
	*
	* <returns> Returns a pointer to the added TACEntry. </returns>
	*/
	TACEntry* AddEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* rightSymbol, Symbol* resultSymbol);

	/**
	* <summary> Gets the internal list of TACEntries. </summary>
	*
	* <returns> Returns the list of TACEntries. </returns>
	*/
	std::list<TACEntry*> GetEntries();

	/**
	* <summary> Gets the index of the last added element. </summary>
	*
	* <returns> Returns the index of the last added element. </returns>
	*/
	size_t GetLastElementIndex();

	/**
	* <summary> Clears the list of TACEntries. </summary>
	*/
	void CleanEntries();

	/**
	* <summary> Prints debug informatino to the stream. Only in debug mode. </summary>
	*
	* <param name="ostream"> The stream that will be written. </param>
	*/
	virtual void Print(std::ostream& ostream);

	/**
	* <summary> Destructor. </summary>
	*/
	virtual ~TACGenerator();
private:
	std::list<TACEntry*> _tacEntries;
};

#endif