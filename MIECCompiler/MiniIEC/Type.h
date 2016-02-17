#ifndef TYPE_H
#define TYPE_H

#include<string>

#include "Object.h"

class Type : public Object
{
public:
	 /**
	 * <summary>  Get size of the type. </summary>
	 *
	 * <returns> Size of type. </returns>
	 */
	 size_t GetSize();

	 /**
	 * <summary>  Get typename of the type. </summary>
	 *
	 * <returns> Typename of type. </returns>
	 */
	 virtual std::string GetTypeName() const = 0;

protected:
	 Type(size_t size);

private:
	 size_t _size;
};

#endif