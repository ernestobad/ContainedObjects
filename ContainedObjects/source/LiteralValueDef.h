#pragma once

#include "ValueDef.h"
#include <antlr3defs.h>
#include "ast_types.h"

namespace COBJ
{
	enum literal_type
	{
		INTEGER_LITERAL,
		FLOAT_LITERAL,
		STRING_LITERAL
	};

	class LiteralValueDef : public ValueDef
	{
	public:
		LiteralValueDef(literal_type literalType, const pANTLR3_BASE_TREE node);
		LiteralValueDef(literal_type literalType);

		virtual ~LiteralValueDef(void);

		virtual ast_node_type getASTNodeType() const = 0;

		literal_type getLiteralType() const
		{
			return m_LiteralType;
		}

		void setLiteralType(literal_type literalType)
		{
			m_LiteralType = literalType;
		}

	private:
		literal_type m_LiteralType;
	};
}
