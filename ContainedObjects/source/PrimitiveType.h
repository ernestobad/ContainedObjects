#pragma once

#include "Type.h"
#include <antlr3defs.h>

namespace COBJ
{
	enum primitive_type {
		FLOAT_P_TYPE = FLOAT_TYPE,
		INTEGER_P_TYPE = INTEGER_TYPE,
		STRING_P_TYPE = STRING_TYPE
	};

	class PrimitiveType : public Type
	{
	public:
		PrimitiveType(primitive_type primitiveType);
		PrimitiveType(const pANTLR3_BASE_TREE node);
		~PrimitiveType(void);

		bool operator==(const Type& type) const;
	};
}
