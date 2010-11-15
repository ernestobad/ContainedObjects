#include "platform.h"
#include "InterfaceDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "FormalParamDef.h"
#include "VariableDeclDef.h"

namespace COBJ
{
	InterfaceDef::InterfaceDef(void)
	{
	}

	InterfaceDef::InterfaceDef(const pANTLR3_BASE_TREE node)
		: ASTNode(node)
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
			m_InterfaceName = (wchar_t*) n->getText(n)->chars;
		}

		{
			// class params
			n = (pANTLR3_BASE_TREE) node->getChild(node, 0);
			assert(n->getType(n) == N_FORMAL_CLASS_PARAMS);

			m_FormalPrameters.clear();

			int childCount = n->getChildCount(n);
			for (int i = 0; i < childCount; i++)
			{
				c = (pANTLR3_BASE_TREE) n->getChild(n, i);
				assert(c->getType(c) == N_FORMAL_CLASS_PARAM);

				boost::shared_ptr<FormalParamDef> pFormalParamDef(new FormalParamDef(c));
				m_FormalPrameters.push_back(pFormalParamDef);
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
		}
	}

	InterfaceDef::~InterfaceDef(void)
	{
	}
}
