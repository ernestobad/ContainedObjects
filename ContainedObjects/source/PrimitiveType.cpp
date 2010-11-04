#include "platform.h"
#include "PrimitiveType.h"

namespace COBJ
{
	PrimitiveType::PrimitiveType(primitive_type primitiveType)
		: Type((basic_type) primitiveType)
	{
	}

	PrimitiveType::~PrimitiveType(void)
	{
	}

	bool PrimitiveType::operator==(const Type& type) const
	{
		return (this->getBasicType() == type.getBasicType());
	}
}