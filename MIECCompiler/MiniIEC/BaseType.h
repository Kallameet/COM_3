#ifndef BASETYPE_H
#define BASETYPE_H

#include "Type.h"

enum class BaseTypeName { INT, FLOAT, CHAR };

class BaseType : public Type
{
public:
	BaseType(BaseTypeName typeName);

	std::string GetTypeName() const;

private:	
	BaseTypeName _typeName;

	size_t ResolveTypeToSize(BaseTypeName typeName);
};

#endif