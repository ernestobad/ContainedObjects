#include "platform.h"
#include "Type.h"
#include "ArrayType.h"
#include "PrimitiveType.h"
#include "ReferenceType.h"
#include "antlr/ContainedObjectsLexer.h"

namespace COBJ
{
	Type::Type(basic_type basicType)
		: ASTNode(), m_BasicType(basicType)
	{
	}

	Type::Type(basic_type basicType, const pANTLR3_BASE_TREE node)
		: ASTNode(node), m_BasicType(basicType)
	{
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

	void createType(
				const pANTLR3_BASE_TREE node,
				TypePtr& pType)
	{
		assert(node->getType(node) == N_TYPE);
		assert(node->getChildCount(node) == 1);

		pANTLR3_BASE_TREE n;

		n = (pANTLR3_BASE_TREE) node->getChild(node, 0);

		if (n->getType(n) == N_ARRAY_TYPE)
		{
			pType = boost::shared_ptr<Type>(static_cast<Type*>(new ArrayType(n)));
		}
		else if (n->getType(n) == N_SIMPLE_TYPE)
		{
			createSimpleType(n, pType);
		}
	}

	void createSimpleType(
			const pANTLR3_BASE_TREE node,
			TypePtr& pType)
	{
		assert(node->getType(node) == N_SIMPLE_TYPE);
		assert(node->getChildCount(node) == 1);

		pANTLR3_BASE_TREE n;

		n = (pANTLR3_BASE_TREE) node->getChild(node, 0);

		ANTLR3_UINT32 type = n->getType(n);

		if ((type == N_INTEGER_TYPE) ||
				(type == N_FLOAT_TYPE) ||
				(type == N_STRING_TYPE))
		{
			pType = boost::shared_ptr<Type>(static_cast<Type*>(new PrimitiveType(n)));
		}
		else if ((type == N_OBJECT_TYPE) ||
				(type == N_CLASS_TYPE))
		{
			pType = boost::shared_ptr<Type>(static_cast<Type*>(new ReferenceType(n)));
		}
		else
		{
			assert(false);
		}
	}
}
