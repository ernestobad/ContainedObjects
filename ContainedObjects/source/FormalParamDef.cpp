/*
 * FormalParamDef.cpp
 *
 *  Created on: Oct 20, 2010
 *      Author: Ernesto
 */

#include "platform.h"
#include "FormalParamDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "Type.h"

namespace COBJ {

	FormalParamDef::FormalParamDef()
	{
	}

	FormalParamDef::FormalParamDef(const pANTLR3_BASE_TREE node)
		: ASTNode(node)
	{
		assert(node->getType(node) == N_FORMAL_CLASS_PARAM);

		pANTLR3_BASE_TREE n, c;

		{
			// type
			n = (pANTLR3_BASE_TREE) node->getChild(node, 0);
			assert(n->getType(n) == N_TYPE);
			createType(n, m_pType);
		}

		{
			// variable name
			n = (pANTLR3_BASE_TREE) node->getChild(node, 1);
			assert(n->getType(n) == N_VAR_NAME);
			assert(n->getChildCount(n) == 1);

			n = (pANTLR3_BASE_TREE) n->getChild(n, 0);
			assert(n->getType(n) == ID);

			m_ParamName = (const wchar_t*) n->getText(n)->chars;
		}
	}

	FormalParamDef::~FormalParamDef()
	{
	}
}
