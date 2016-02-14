#ifndef TYPE_H
#define TYPE_H

#include<string>

#include "Object.h"

class Type : public Object
{
public:	
	size_t GetSize();
	virtual std::string GetTypeName() const = 0;

protected:
	Type(size_t size);	

private:
	size_t _size;
};

#endif