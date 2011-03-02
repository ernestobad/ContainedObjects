#include "platform.h"
#include "ReferencePathValueDef.h"
#include "antlr/ContainedObjectsLexer.h"

namespace COBJ
{
	ReferencePathValueDef::ReferencePathValueDef(void)
		: ValueDef(REFERENCE_PATH)
	{
	}

	ReferencePathValueDef::ReferencePathValueDef(const pANTLR3_BASE_TREE node)
		: ValueDef(REFERENCE_PATH, node)
	{
		assert(node->getType(node) == N_REFERENCE_VAL);
		assert(node->getChildCount(node) >= 1);

		pANTLR3_BASE_TREE c;

		m_ReferencePath.clear();

		int childCount = node->getChildCount(node);
		for (int i = 0; i < childCount; i++)
		{
			c = (pANTLR3_BASE_TREE) node->getChild(node, i);
			assert(c->getType(c) == ID);

			wchar_t* szId = (wchar_t*) c->getText(c)->chars;

			m_ReferencePath.push_back(szId);
		}
	}

	ReferencePathValueDef::~ReferencePathValueDef(void)
	{
	}
}
