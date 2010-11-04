#pragma once

#include "LiteralValueDef.h"

namespace COBJ
{
	class IntegerLiteralValueDef : public LiteralValueDef
	{
	public:
		IntegerLiteralValueDef(void);
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
