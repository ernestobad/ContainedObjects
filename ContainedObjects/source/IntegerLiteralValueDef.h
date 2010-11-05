#pragma once

#include "LiteralValueDef.h"
#include <antlr3defs.h>

namespace COBJ
{
	class IntegerLiteralValueDef : public LiteralValueDef
	{
	public:
		IntegerLiteralValueDef(void);
		IntegerLiteralValueDef(const pANTLR3_BASE_TREE node);
		virtual ~IntegerLiteralValueDef(void);

		int getIntValue() const
		{
			return m_IntValue;
		}

		void setIntValue(const int intValue)
		{
			m_IntValue = intValue;
		}

	private:
		int m_IntValue;
	};
}