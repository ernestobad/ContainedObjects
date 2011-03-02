#pragma once

#include "ValueDef.h"
#include "ASTNode.h"
#include <antlr3defs.h>

namespace COBJ
{
	using namespace std;

	class ReferencePathValueDef : public ValueDef
	{
	public:
		ReferencePathValueDef(void);
		ReferencePathValueDef(const pANTLR3_BASE_TREE node);

		~ReferencePathValueDef(void);

		ast_node_type getASTNodeType() const
		{
			return ASTN_REFERENCE_PATH_VALUE;
		}

		void getChildNodes(list<ASTNodePtr>& children) const
		{
		}

		const list<const wstring>& getReferencePath() const
		{
			return m_ReferencePath;
		}

		void setReferencePath(list<const wstring>& referencePath)
		{
			m_ReferencePath = referencePath;
		}

	private:
		list<const wstring> m_ReferencePath;
	};
}
