#pragma once

#include "LiteralValueDef.h"
#include <antlr3defs.h>
#include "ast_types.h"

namespace COBJ
{
	class FloatLiteralValueDef : public LiteralValueDef
	{
	public:
		FloatLiteralValueDef(void);
		FloatLiteralValueDef(const pANTLR3_BASE_TREE node);

		virtual ~FloatLiteralValueDef(void);

		ast_node_type getASTNodeType() const
		{
			return ASTN_FLOAT_LITERAL_VALUE;
		}

		void getChildNodes(std::list<ASTNodePtr>& children) const
		{
		}

		float getFloatValue() const
		{
			return m_FloatValue;
		}

		void setFloatValue(const float floatValue)
		{
			m_FloatValue = floatValue;
		}

	private:
		float m_FloatValue;
	};
}
