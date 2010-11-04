/*
 * ClassDef.cpp
 *
 *  Created on: Oct 20, 2010
 *      Author: Ernesto Badillo
 */


#include "platform.h"
#include "ClassDef.h"
#include "antlr/ContainedObjectsLexer.h"


namespace COBJ
{
	ClassDef::ClassDef() :
			m_IsNative(false)
	{
	}

	static void create(const pANTLR3_BASE_TREE node, boost::shared_ptr<ClassDef>& pClassDef)
	{
		assert(node->getType(node) == N_CLASS_DECL);
		assert(node->getChildCount(node) == 4);

		pClassDef = boost::shared_ptr<ClassDef>(new ClassDef());
		
		{ // class name
			pANTLR3_BASE_TREE nodeClassName = (pANTLR3_BASE_TREE) node->getChild(node, 0);
			pANTLR3_BASE_TREE nodeClassNameId = (pANTLR3_BASE_TREE) nodeClassName->getChild(nodeClassName, 0);
			pANTLR3_STRING nodeClassNameIdText = (pANTLR3_STRING) nodeClassNameId->getText(nodeClassNameId);
			std::wstring className((const wchar_t*) nodeClassNameIdText->chars);
			pClassDef->setClassName(className);
		}

		{ // formal class params
			pANTLR3_BASE_TREE nodeFormalClassParams = (pANTLR3_BASE_TREE) node->getChild(node, 1);
			int childCount = nodeFormalClassParams->getChildCount(nodeFormalClassParams);
			for (int i = 0; i < childCount; i++)
			{
				pANTLR3_BASE_TREE sdsd = (pANTLR3_BASE_TREE) nodeFormalClassParams->getChild(nodeFormalClassParams, i);

			}
		}

	}

	ClassDef::~ClassDef()
	{
	}
}
