#pragma once

#include "ValueDef.h"

namespace COBJ
{
	enum literal_type
	{
		INTEGER_LITERAL, FLOAT_LITERAL, STRING_LITERAL
	};

	class LiteralValueDef : ValueDef
	{
	public:
		LiteralValueDef(literal_type literalType);
		virtual ~LiteralValueDef(void);

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
