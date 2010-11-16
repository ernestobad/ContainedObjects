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
			m_BasicType = INTEGER_B_TYPE;
		}
		else if (node->getType(node) == N_FLOAT_TYPE)
		{
			m_BasicType = FLOAT_B_TYPE;
		}
		else if (node->getType(node) == N_STRING_TYPE)
		{
			m_BasicType = STRING_B_TYPE;
		}
		else
		{
			assert(false);
		}
	}

	PrimitiveType::~PrimitiveType(void)
	{
	}

	primitive_type PrimitiveType::getPrimitiveType() const
	{
		return static_cast<primitive_type>(m_BasicType);
	}

	std::wstring PrimitiveType::toString() const
	{
		switch (getPrimitiveType())
		{
		case FLOAT_P_TYPE:
			return std::wstring(L"float");
		case INTEGER_P_TYPE:
			return std::wstring(L"integer");
		case STRING_P_TYPE:
			return std::wstring(L"string");
		default:
			assert(false);
			return std::wstring(L"");
		}
	}

	bool PrimitiveType::operator==(const Type& type) const
	{
		return (this->getBasicType() == type.getBasicType());
	}
}
