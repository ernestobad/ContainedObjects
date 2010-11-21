#include "platform.h"
#include "PrimitiveType.h"
#include "antlr/ContainedObjectsLexer.h"
#include "exceptions.h"

namespace COBJ
{
	PrimitiveType::PrimitiveType(primitive_type primitiveType)
		: Type((basic_type) primitiveType)
	{
	}

	basic_type getPrimitiveBasicType(const pANTLR3_BASE_TREE node)
	{
		if (node->getType(node) == N_INTEGER_TYPE)
		{
			return INTEGER_B_TYPE;
		}
		else if (node->getType(node) == N_FLOAT_TYPE)
		{
			return FLOAT_B_TYPE;
		}
		else if (node->getType(node) == N_STRING_TYPE)
		{
			return STRING_B_TYPE;
		}
		else
		{
			std::wstring msg(L"Invalid node");
			InternalErrorException e(msg);
			throw e;
		}
	}

	PrimitiveType::PrimitiveType(const pANTLR3_BASE_TREE node)
		: Type(getPrimitiveBasicType(node), node)
	{
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
