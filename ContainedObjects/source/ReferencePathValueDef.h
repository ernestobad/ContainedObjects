#pragma once

#include "ValueDef.h"
#include "ASTNode.h"
#include <antlr3defs.h>

namespace COBJ
{
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

		void getChildNodes(std::list<ASTNodePtr>& children) const
		{
		}

		const std::list<std::wstring>& getReferencePath() const
		{
			return m_ReferencePath;
		}

		void setReferencePath(std::list<std::wstring>& referencePath)
		{
			m_ReferencePath = referencePath;
		}

	private:
		std::list<std::wstring> m_ReferencePath;
	};
}
