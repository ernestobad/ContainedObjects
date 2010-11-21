/*
 * ActualParamDef.cpp
 *
 *  Created on: Oct 22, 2010
 *      Author: Ernesto
 */

#include "platform.h"
#include "ActualParamDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "ValueDef.h"

namespace COBJ {

	ActualParamDef::ActualParamDef()
	{
	}

	ActualParamDef::ActualParamDef(const pANTLR3_BASE_TREE node)
		: ASTNode(node)
	{
		assert(node->getType(node) == N_ACTUAL_PARAM);
		assert(node->getChildCount(node) == 2);

		pANTLR3_BASE_TREE n;

		{
			// param name
			n = (pANTLR3_BASE_TREE) node->getChild(node, 0);
			assert(n->getType(n) == N_PARAM_NAME);

			m_ParamName = (wchar_t*) n->getText(n)->chars;
		}

		{
			// value
			n = (pANTLR3_BASE_TREE) node->getChild(node, 1);
			assert(n->getType(n) == N_VALUE);

			createValueDef(n, m_pValue);
		}
	}

	ActualParamDef::~ActualParamDef() {
	}

	void ActualParamDef::getChildNodes(std::list<ASTNodePtr>& children) const
	{
		children.push_back(m_pValue);
	}

}
