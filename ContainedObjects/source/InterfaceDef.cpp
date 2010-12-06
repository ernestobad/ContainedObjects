#include "platform.h"
#include "InterfaceDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "FormalParamDef.h"
#include "VariableDeclDef.h"

namespace COBJ
{
	bool alphabeticalOrderCompare(VariableDeclDefPtr& first, VariableDeclDefPtr& second)
	{
		const wstring& name1 = first->getName();
		const wstring& name2 = second->getName();

		return boost::algorithm::lexicographical_compare(
			name1, name2, boost::is_iless());
	}

	InterfaceDef::InterfaceDef(void)
	{
	}

	InterfaceDef::InterfaceDef(const pANTLR3_BASE_TREE node)
		: ClassDefBase(node)
	{
		assert(node->getType(node) == N_IFACE_DECL);
		assert(node->getChildCount(node) == 3);

		pANTLR3_BASE_TREE n, c;

		{
			// Name
			n = (pANTLR3_BASE_TREE) node->getChild(node, 0);
			assert(n->getType(n) == N_IFACE_NAME);
			assert(n->getChildCount(n) == 1);

			n = (pANTLR3_BASE_TREE) n->getChild(n, 0);
			assert(n->getType(n) == ID);
			m_ClassName = (wchar_t*) n->getText(n)->chars;
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
			// body
			n = (pANTLR3_BASE_TREE) node->getChild(node, 1);
			assert(n->getType(n) == N_BODY);

			m_VariableDecls.clear();

			int childCount = n->getChildCount(n);
			for (int i = 0; i < childCount; i++)
			{
				c = (pANTLR3_BASE_TREE) n->getChild(n, i);
				assert(c->getType(c) == N_VARDEF);

				boost::shared_ptr<VariableDeclDef> pVariableDeclDef(new VariableDeclDef(c));
				m_VariableDecls.push_back(pVariableDeclDef);
			}

			m_VariableDecls.sort(alphabeticalOrderCompare);
		}
	}

	InterfaceDef::~InterfaceDef(void)
	{
	}

	void InterfaceDef::getChildNodes(std::list<ASTNodePtr>& children) const
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
