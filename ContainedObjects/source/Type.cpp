#include "platform.h"
#include "Type.h"

namespace COBJ
{
	Type::Type(basic_type basicType)
	{
		m_BasicType = basicType;
	}

	Type::~Type()
	{
	}

	basic_type Type::getBasicType() const
	{
		return m_BasicType;
	}

	bool Type::operator!=(const Type& type) const
	{
		return !(*this == type);
	}
}