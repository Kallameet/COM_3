#ifndef TACENTRY_H
#define TACENTRY_H

#include "Object.h"
#include "OpKind.h"
#include "Symbol.h"
#include "CodeGenProl16\CodeGenProl16.h"

class TACEntry : public Object
{
public:
	/**
	* <summary> Constructor. </summary>
	*
	* <param name="operatorKind"> The operator of the TACEntry that will be created. </param>
	* <param name="leftSymbol"> The left symbol of the TACEntry that will be created. </param>
	* <param name="resultSymbol"> The result symbol of the TACEntry that will be created. </param>
	*/
	TACEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* resultSymbol);

	/**
	* <summary> Constructor. </summary>
	*
	* <param name="operatorKind"> The operator of the TACEntry that will be created. </param>
	* <param name="leftSymbol"> The left symbol of the TACEntry that will be created. </param>
	* <param name="resultSymbol"> The result symbol of the TACEntry that will be created. </param>
	*/
	TACEntry(OpKind operatorKind, Symbol* leftSymbol, Symbol* rightSymbol, Symbol* resultSymbol);

	/**
	* <summary> Gets the left symbol. </summary>
	*
	* <returns> Returns the left symbol of the TACEntry. </returns>
	*/
	Symbol* TACEntry::GetLeftSymbol();

	/**
	* <summary> Gets the rights symbol. </summary>
	*
	* <returns> Returns the right symbol of the TACEntry. </returns>
	*/
	Symbol* TACEntry::GetRightSymbol();

	/**
	* <summary> Gets the result symbol. </summary>
	*
	* <returns> Returns the result symbol of the TACEntry. </returns>
	*/
	Symbol* TACEntry::GetResultSymbol();

	/**
	* <summary> Gets the operator. </summary>
	*
	* <returns> Returns the operator of the TACEntry. </returns>
	*/
	OpKind GetOperatorKind();


	/**
	* <summary> Sets the left symbol. </summary>
	*
	* <param name="symbol"> Sets the left symbol of the TACEntry. </param>
	*/
	void SetLeftSymbol(Symbol* symbol);

	/**
	* <summary> Sets the right symbol. </summary>
	*
	* <param name="symbol"> Sets the right symbol of the TACEntry. </param>
	*/
	void SetRightSymbol(Symbol* symbol);

	/**
	* <summary> Sets the result symbol. </summary>
	*
	* <param name="symbol"> Sets the result symbol of the TACEntry. </param>
	*/
	void SetResultSymbol(Symbol* symbol);


	/**
	* <summary> Sets the entry address. Used by code generator. Address is the address of the first assembler instruction of the TACEntry. </summary>
	*
	* <param name="symbol"> The address. </param>
	*/
	void SetEntryAddress(WORD address);

	/**
	* <summary> Gets the entry address. </summary>
	*
	* <returns> Returns the entry address in a Word. </returns>
	*/
	WORD GetEntryAddress();


	/**
	* <summary> Prints debug informatino to the stream. Only in debug mode. </summary>
	*
	* <param name="ostream"> The stream that will be written. </param>
	*/
	virtual void Print(std::ostream& ostream);

	/**
	* <summary> Destructor. </summary>
	*/
	virtual ~TACEntry();
	
private:
	OpKind _operatorKind;

	Symbol* _leftSymbol;
	Symbol* _rightSymbol;
	Symbol* _resultSymbol;

	WORD _address;
	int _tmpResult;
};

#endif