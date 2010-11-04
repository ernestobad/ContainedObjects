#pragma once

#include "LiteralValueDef.h"

namespace COBJ
{
	class StringLiteralValueDef : public LiteralValueDef
	{
	public:
		StringLiteralValueDef(void);
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
