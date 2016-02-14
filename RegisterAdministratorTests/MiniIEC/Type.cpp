#include "Type.h"

Type::Type(size_t size)
{
	_size = size;
}

size_t Type::GetSize()
{
	return _size;
}
