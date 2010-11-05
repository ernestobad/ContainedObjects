#pragma once

#include "LiteralValueDef.h"
#include <antlr3defs.h>

namespace COBJ
{
	class StringLiteralValueDef : public LiteralValueDef
	{
	public:
		StringLiteralValueDef(void);
		StringLiteralValueDef(const pANTLR3_BASE_TREE node);

		virtual ~StringLiteralValueDef(void);

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
