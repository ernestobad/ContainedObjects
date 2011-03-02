#pragma once

#include "LiteralValueDef.h"
#include <antlr3defs.h>
#include "ast_types.h"

namespace COBJ
{
	class IntegerLiteralValueDef : public LiteralValueDef
	{
	public:
		IntegerLiteralValueDef(void);
		IntegerLiteralValueDef(const pANTLR3_BASE_TREE node);
		virtual ~IntegerLiteralValueDef(void);

		ast_node_type getASTNodeType() const
		{
			return ASTN_INTEGER_LITERAL_VALUE;
		}

		void getChildNodes(std::list<ASTNodePtr>& children) const
		{
		}

		int getIntValue() const
		{
			return m_IntValue;
		}

		void setIntValue(int intValue)
		{
			m_IntValue = intValue;
		}

	private:
		int m_IntValue;
	};
}
