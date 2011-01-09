
#include "platform.h"
#include "ArrayInitValueDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "ArrayType.h"
#include "ValueDef.h"
#include "ASTNode.h"

namespace COBJ
{
	ArrayInitValueDef::ArrayInitValueDef(void)
		: ValueDef(ARRAY_INIT)
	{
	}

	ArrayInitValueDef::ArrayInitValueDef(const pANTLR3_BASE_TREE node)
		: ValueDef(ARRAY_INIT, node)
	{
		assert(node->getType(node) == N_ARRAY_INIT_VAL);
		assert(node->getChildCount(node) == 2);

		pANTLR3_BASE_TREE n, c;

		{
			// type
			n = (pANTLR3_BASE_TREE) node->getChild(node, 0);
			assert(n->getType(n) == N_ARRAY_TYPE);
			
			m_pDeclaredType = boost::shared_ptr<Type>(static_cast<Type*>(new ArrayType(n)));
		}

		{
			// array values
			n = (pANTLR3_BASE_TREE) node->getChild(node, 1);
			assert(n->getType(n) == N_ARRAY_VALUES);

			m_Values.clear();

			int childCount = n->getChildCount(n);
			for (int i = 0; i < childCount; i++)
			{
				c = (pANTLR3_BASE_TREE) n->getChild(n, i);

				boost::shared_ptr<ValueDef> pValueDef;
				createValueDef(c, pValueDef);

				m_Values.push_back(pValueDef);
			}
		}
	}

	ArrayInitValueDef::~ArrayInitValueDef(void)
	{
	}

	void ArrayInitValueDef::getChildNodes(std::list<ASTNodePtr>& children) const
	{
		children.push_back(m_pDeclaredType);

		std::list<ValueDefPtr>::const_iterator it;

		for (it = m_Values.begin(); it != m_Values.end(); it++)
		{
			children.push_back(*it);
		}		
	}
}
