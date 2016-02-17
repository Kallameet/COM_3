#ifndef BASETYPE_H
#define BASETYPE_H

#include "Type.h"

enum class BaseTypeName { INT, FLOAT, CHAR };

class BaseType : public Type
{
public:
	 /**
	 * <summary>  Constructor. </summary>
	 *
	 * <param name="name">   The typename of the basetype. </param>
	 *
	 */
	 BaseType(BaseTypeName typeName);
	 /**
	 * <summary>  Get typename of the basetype. </summary>
	 *
	 * <returns> Typename of basetype.
	 */
	 std::string GetTypeName() const;

private:
	 BaseTypeName _typeName;

	 size_t ResolveTypeToSize(BaseTypeName typeName);
};

#endif