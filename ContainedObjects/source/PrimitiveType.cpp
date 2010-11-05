#include "platform.h"
#include "PrimitiveType.h"
#include "antlr/ContainedObjectsLexer.h"

namespace COBJ
{
	PrimitiveType::PrimitiveType(primitive_type primitiveType)
		: Type((basic_type) primitiveType)
	{
	}

	PrimitiveType::PrimitiveType(const pANTLR3_BASE_TREE node)
		: Type()
	{
		if (node->getType(node) == N_INTEGER_TYPE)
		{
			m_BasicType = INTEGER_TYPE;
		}
		else if (node->getType(node) == N_FLOAT_TYPE)
		{
			m_BasicType = FLOAT_TYPE;
		}
		else if (node->getType(node) == N_STRING_TYPE)
		{
			m_BasicType = STRING_TYPE;
		}
		else
		{
			assert(false);
		}
	}

	PrimitiveType::~PrimitiveType(void)
	{
	}

	bool PrimitiveType::operator==(const Type& type) const
	{
		return (this->getBasicType() == type.getBasicType());
	}
}
