#include "platform.h"
#include "ArrayType.h"
#include "antlr/ContainedObjectsLexer.h"

namespace COBJ
{

	ArrayType::ArrayType(const ConstTypePtr& pChildType)
		: Type(ARRAY_B_TYPE), m_pChildType(pChildType)
	{
	}

	ArrayType::ArrayType(const pANTLR3_BASE_TREE node)
		: Type(ARRAY_B_TYPE)
	{
		assert(node->getType(node) == N_ARRAY_TYPE);
		assert(node->getChildCount(node) == 1);

		pANTLR3_BASE_TREE n;

		n = (pANTLR3_BASE_TREE) node->getChild(node, 0);

		assert(n->getType(n) == N_SIMPLE_TYPE);

		createSimpleType(n, m_pChildType);
	}

	ArrayType::~ArrayType(void)
	{
	}

	const ConstTypePtr& ArrayType::getChildType() const
	{
		return m_pChildType;
	}

	bool ArrayType::operator==(const Type& type) const
	{
		if (type.getBasicType() != this->getBasicType())
		{
			return false;
		}

		const ArrayType& arrayType = static_cast<const ArrayType &>(type);

		const ConstTypePtr& childType1 = arrayType.getChildType();
		const ConstTypePtr& childType2 = getChildType();

		return (*childType1 == *childType2);
	}
}
