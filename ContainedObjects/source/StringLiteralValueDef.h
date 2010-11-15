#pragma once

#include "LiteralValueDef.h"
#include <antlr3defs.h>
#include "ast_types.h"

namespace COBJ
{
	class StringLiteralValueDef : public LiteralValueDef
	{
	public:
		StringLiteralValueDef(void);
		StringLiteralValueDef(const pANTLR3_BASE_TREE node);
		virtual ~StringLiteralValueDef(void);

		ast_node_type getASTNodeType() const
		{
			return ASTN_STRING_LITERAL_VALUE;
		}

		const std::wstring& getStringValue() const
		{
			return m_StringValue;
		}

		void setStringValue(const std::wstring& stringValue)
		{
			m_StringValue = stringValue;
		}

	private:
		std::wstring m_StringValue;
	};
}
