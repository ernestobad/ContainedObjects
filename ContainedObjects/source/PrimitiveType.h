#pragma once

#include "Type.h"

namespace COBJ
{
	enum primitive_type {
		FLOAT_P_TYPE = FLOAT_TYPE,
		INTEGER_P_TYPE = INTEGER_TYPE,
		STRING_P_TYPE = STRING_TYPE
	};

	class PrimitiveType : Type
	{
	public:
		PrimitiveType(primitive_type primitiveType);
		~PrimitiveType(void);

		bool operator==(const Type& type) const;
	};
}