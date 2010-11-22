#pragma once

#include "LiteralValueDef.h"
#include <antlr3defs.h>
#include "ast_types.h"

namespace COBJ
{
	using namespace std;

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

		void getChildNodes(list<ASTNodePtr>& children) const
		{
		}

		const wstring& getStringValue() const
		{
			return m_StringValue;
		}

		void setStringValue(const wstring& stringValue)
		{
			m_StringValue = stringValue;
		}

	private:
		wstring m_StringValue;
	};
}
