#pragma once

#include "ValueDef.h"

namespace COBJ
{
	class ReferencePathValueDef : ValueDef
	{
	public:
		ReferencePathValueDef(void);
		~ReferencePathValueDef(void);

		const std::list<std::wstring>& getReferencePath() const
		{
			return m_ReferencePath;
		}

		void setReferencePath(std::list<std::wstring>& referencePath)
		{
			m_ReferencePath = referencePath;
		}

	private:
		std::list<std::wstring> m_ReferencePath;
	};
}