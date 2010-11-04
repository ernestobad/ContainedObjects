#pragma once

#include "LiteralValueDef.h"

namespace COBJ
{
	class FloatLiteralValueDef : public LiteralValueDef
	{
	public:
		FloatLiteralValueDef(void);
		virtual ~FloatLiteralValueDef(void);

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
