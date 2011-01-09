/*
 * ValueDef.cpp
 *
 *  Created on: Oct 21, 2010
 *      Author: Ernesto
 */

#include "platform.h"
#include "ValueDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "ObjectInitValueDef.h"
#include "ArrayInitValueDef.h"
#include "IntegerLiteralValueDef.h"
#include "FloatLiteralValueDef.h"
#include "StringLiteralValueDef.h"
#include "ReferencePathValueDef.h"

namespace COBJ {

	ValueDef::ValueDef(value_type valueType, const pANTLR3_BASE_TREE node)
		: ASTNode(node), m_ValueType(valueType)
	{
	}

	ValueDef::ValueDef(value_type valueType)
		: m_ValueType(valueType)
	{
	}

	ValueDef::~ValueDef()
	{
	}

	void createValueDef(
			const pANTLR3_BASE_TREE node,
			boost::shared_ptr<ValueDef>& pType)
	{
		assert(node->getType(node) == N_VALUE);
		int temp = node->getChildCount(node);
		assert(node->getChildCount(node) == 1);

		pANTLR3_BASE_TREE n;
		
		n = (pANTLR3_BASE_TREE) node->getChild(node, 0);

		switch (n->getType(n))
		{
		case N_OBJECT_INIT_VAL:
			pType = boost::shared_ptr<ValueDef>(static_cast<ValueDef*>(new ObjectInitValueDef(n)));
			break;
		case N_ARRAY_INIT_VAL:
			pType = boost::shared_ptr<ValueDef>(static_cast<ValueDef*>(new ArrayInitValueDef(n)));
			break;
		case N_LITERAL_VAL:
			assert(n->getChildCount(n) == 1);
			n = (pANTLR3_BASE_TREE) n->getChild(n, 0);
			switch (n->getType(n))
			{
			case N_INT_LITERAL:
				pType = boost::shared_ptr<ValueDef>(static_cast<ValueDef*>(new IntegerLiteralValueDef(n)));
				break;
			case N_FLOAT_LITERAL:
				pType = boost::shared_ptr<ValueDef>(static_cast<ValueDef*>(new FloatLiteralValueDef(n)));
				break;
			case N_STRING_LITERAL:
				pType = boost::shared_ptr<ValueDef>(static_cast<ValueDef*>(new StringLiteralValueDef(n)));
				break;
			default:
				assert(false);
				break;
			}
			break;
		case N_REFERENCE_VAL:
			pType = boost::shared_ptr<ValueDef>(static_cast<ValueDef*>(new ReferencePathValueDef(n)));
			break;
		default:
			assert(false);
			break;
		}
	}
}
