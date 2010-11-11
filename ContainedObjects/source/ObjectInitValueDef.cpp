#include "platform.h"
#include "ObjectInitValueDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "ActualParamDef.h"

namespace COBJ
{
	ObjectInitValueDef::ObjectInitValueDef(void)
	{
	}

	ObjectInitValueDef::ObjectInitValueDef(const pANTLR3_BASE_TREE node)
	{
		assert(node->getType(node) == N_OBJECT_INIT_VAL);
		assert(node->getChildCount(node) == 2);

		pANTLR3_BASE_TREE n, c;

		{
			// class name
			n = (pANTLR3_BASE_TREE) node->getChild(node, 0);
			assert(n->getType(n) == N_CLASS_NAME);
			assert(n->getChildCount(n) == 1);

			n = (pANTLR3_BASE_TREE) n->getChild(n, 0);
			assert(n->getType(n) == ID);

			wchar_t* szClassName = (wchar_t*) n->getText(n)->chars;
			m_ClassName = szClassName;
		}

		{
			m_ActualParams.clear();

			// actual params
			n = (pANTLR3_BASE_TREE) node->getChild(node, 1);
			assert(n->getType(n) == N_ACTUAL_PARAMS);

			int childCount = n->getChildCount(n);
			for (int i = 0; i < childCount; i++)
			{
				c = (pANTLR3_BASE_TREE) n->getChild(n, i);
				assert(c->getType(c) == N_ACTUAL_PARAM);

				boost::shared_ptr<ActualParamDef> pActualParamDef(new ActualParamDef(c));
				m_ActualParams.push_back(pActualParamDef);
			}
		}
	}

	ObjectInitValueDef::~ObjectInitValueDef(void)
	{
	}
}
