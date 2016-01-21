#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <iostream>
#include "Object.h"
#include "Type.h"

class Symbol : public Object
{
public:
	Symbol(std::string const& name, Type* type);

	std::string GetName();

	Type* GetType();

	virtual void Print(std::ostream& ostream);

private:
	std::string _name;
	Type* _type;
};

#endif