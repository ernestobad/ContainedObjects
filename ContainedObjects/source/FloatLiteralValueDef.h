#pragma once

#include "LiteralValueDef.h"
#include <antlr3defs.h>

namespace COBJ
{
	class FloatLiteralValueDef : public LiteralValueDef
	{
	public:
		FloatLiteralValueDef(void);
		FloatLiteralValueDef(const pANTLR3_BASE_TREE node);

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
