#pragma once

#include "Type.h"
#include <antlr3defs.h>

namespace COBJ
{
	enum primitive_type
	{
		FLOAT_P_TYPE = FLOAT_B_TYPE,
		INTEGER_P_TYPE = INTEGER_B_TYPE,
		STRING_P_TYPE = STRING_B_TYPE
	};

	class PrimitiveType : public Type
	{
	public:
		PrimitiveType(primitive_type primitiveType);
		PrimitiveType(const pANTLR3_BASE_TREE node);
		~PrimitiveType(void);

		bool operator==(const Type& type) const;
	};

	const boost::shared_ptr<Type> P_FLOAT_TYPE = 
		boost::shared_ptr<PrimitiveType>(new PrimitiveType(FLOAT_P_TYPE));

	const boost::shared_ptr<Type> P_INTEGER_TYPE = 
		boost::shared_ptr<PrimitiveType>(new PrimitiveType(INTEGER_P_TYPE));

	const boost::shared_ptr<Type> P_STRING_TYPE = 
		boost::shared_ptr<PrimitiveType>(new PrimitiveType(STRING_P_TYPE));
}
