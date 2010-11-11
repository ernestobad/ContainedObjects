/*
 * VariableDeclDef.cpp
 *
 *  Created on: Oct 21, 2010
 *      Author: Ernesto
 */

#include "platform.h"
#include "VariableDeclDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "Type.h"
#include "ValueDef.h"

namespace COBJ
{

	VariableDeclDef::VariableDeclDef()
	{
	}

	VariableDeclDef::VariableDeclDef(const pANTLR3_BASE_TREE node)
	{
		assert(node->getType(node) == N_VARDEF);
		assert(node->getChildCount(node) == 3 || node->getChildCount(node) == 4);

		pANTLR3_BASE_TREE n, c;

		bool hasValue = (node->getChildCount(node) == 4);

		{
			// scope
			n = (pANTLR3_BASE_TREE) node->getChild(node, 0);
			assert(n->getType(n) == N_SCOPE);

			m_IsStatic = false;

			int childCount = n->getChildCount(n);
			if (childCount > 0)
			{
				assert(childCount == 1);
				n = (pANTLR3_BASE_TREE) n->getChild(n, 0);
				assert(n->getType(n) == STATIC_KW);
				m_IsStatic = true;
			}
		}

		{
			// type
			n = (pANTLR3_BASE_TREE) node->getChild(node, 1);
			assert(n->getType(n) == N_TYPE);

			createType(n, m_pDeclaredType);
		}

		{
			// Variable name
			n = (pANTLR3_BASE_TREE) node->getChild(node, 2);
			assert(n->getType(n) == N_VAR_NAME);
			assert(n->getChildCount(n) == 1);

			n = (pANTLR3_BASE_TREE) n->getChild(n, 0);
			assert(n->getType(n) == ID);
			m_Name = (wchar_t*) n->getText(n)->chars;
		}

		if (hasValue)
		{
			// Value
			n = (pANTLR3_BASE_TREE) node->getChild(node, 3);
			assert(n->getType(n) == N_VALUE);
			
			createValueDef(n, m_pValue);
		}
		else
		{
			m_pValue = boost::shared_ptr<ValueDef>(); // NULL
		}
	}

	VariableDeclDef::~VariableDeclDef()
	{
	}

}
