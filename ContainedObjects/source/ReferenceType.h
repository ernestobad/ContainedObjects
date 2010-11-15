#pragma once

#include "Type.h"
#include <antlr3defs.h>

namespace COBJ
{
	enum reference_type
	{
		OBJECT_REF_TYPE = OBJECT_B_TYPE,
		CLASS_REF_TYPE = CLASS_B_TYPE
	};

	class ReferenceType : public Type
	{
	public:
		ReferenceType(reference_type referenceType, const std::wstring& referenceTypeName);

		ReferenceType(const pANTLR3_BASE_TREE node);

		~ReferenceType(void);

		
		reference_type getReferenceType() const;

		const std::wstring& getReferenceTypeName() const;

		bool operator==(const Type& type) const;

	private:
		std::wstring m_ReferenceTypeName;
	};
}
