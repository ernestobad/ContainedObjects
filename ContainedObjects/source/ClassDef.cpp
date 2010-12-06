/*
 * ClassDef.cpp
 *
 *  Created on: Oct 20, 2010
 *      Author: Ernesto Badillo
 */


#include "platform.h"
#include "ClassDef.h"
#include "FormalParamDef.h"
#include "VariableDeclDef.h"
#include "antlr/ContainedObjectsLexer.h"


namespace COBJ
{
	ClassDef::ClassDef()
		: ClassDefBase()
	{
	}

	ClassDef::ClassDef(const pANTLR3_BASE_TREE node)
		: ClassDefBase(node)
	{
		assert(node->getType(node) == N_CLASS_DECL);
		assert(node->getChildCount(node) == 4);

		pANTLR3_BASE_TREE n, c;

		{
			// class name

			n = (pANTLR3_BASE_TREE) node->getChild(node, 0);
			assert(n->getType(n) == N_CLASS_NAME);

			n = (pANTLR3_BASE_TREE) n->getChild(n, 0);
			assert(n->getType(n) == ID);

			m_ClassName = (const wchar_t*) n->getText(n)->chars;
		}

		{
			// formal class params

			m_FormalParametersMap.clear();

			n = (pANTLR3_BASE_TREE) node->getChild(node, 1);
			assert(n->getType(n) == N_FORMAL_CLASS_PARAMS);

			int childCount = n->getChildCount(n);
			for (int i = 0; i < childCount; i++)
			{
				c = (pANTLR3_BASE_TREE) n->getChild(n, i);
				assert(c->getType(c) == N_FORMAL_CLASS_PARAM);

				FormalParamDefPtr pFormalParamDef(new FormalParamDef(c));
				m_FormalParametersMap[pFormalParamDef->getParamName()] = pFormalParamDef;
			}
		}

		{
			// Implements decl

			n = (pANTLR3_BASE_TREE) node->getChild(node, 2);
			assert(n->getType(n) == N_IMPLEMENTS_DECL);

			m_ImplementedInterfaces.clear();

			int childCount = n->getChildCount(n);
			for (int i = 0; i < childCount; i++)
			{
				c = (pANTLR3_BASE_TREE) n->getChild(n, i);
				assert(c->getType(c) == N_IMPLEMENTED_IFACE);

				c = (pANTLR3_BASE_TREE) c->getChild(c, 0);
				assert(c->getType(c) == ID);

				m_ImplementedInterfaces.push_back((const wchar_t*) c->getText(c)->chars);
			}
		}

		{
			// body

			n = (pANTLR3_BASE_TREE) node->getChild(node, 3);
			assert(n->getType(n) == N_BODY);

			m_VariableDecls.clear();

			int childCount = n->getChildCount(n);
			for (int i = 0; i < childCount; i++)
			{
				c = (pANTLR3_BASE_TREE) n->getChild(n, i);
				assert(c->getType(c) == N_VARDEF_ASSIGN);

				boost::shared_ptr<VariableDeclDef> pVarDeclAssign(new VariableDeclDef(c));
				m_VariableDecls.push_back(pVarDeclAssign);
			}
		}
	}

	ClassDef::~ClassDef()
	{
	}

	void ClassDef::getChildNodes(std::list<ASTNodePtr>& children) const
	{
		list<VariableDeclDefPtr>::const_iterator vit;

		for (vit = m_VariableDecls.begin(); vit != m_VariableDecls.end(); vit++)
		{
			children.push_back(*vit);
		}

		map<const wstring, FormalParamDefPtr>::const_iterator fit;

		for (fit = m_FormalParametersMap.begin(); fit != m_FormalParametersMap.end(); fit++)
		{
			children.push_back((*fit).second);
		}
	}

	
}
