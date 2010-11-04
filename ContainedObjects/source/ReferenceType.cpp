#include "platform.h"
#include "ReferenceType.h"

namespace COBJ
{
	ReferenceType::ReferenceType(reference_type referenceType, const std::wstring& referenceTypeName)
		: Type((basic_type) referenceType), m_ReferenceTypeName(referenceTypeName)
	{
	}

	ReferenceType::~ReferenceType(void)
	{
	}

	const std::wstring& ReferenceType::getReferenceTypeName() const
	{
		return m_ReferenceTypeName;
	}

	bool ReferenceType::operator==(const Type& type) const
	{
		if (type.getBasicType() != this->getBasicType())
		{
			return false;
		}

		const ReferenceType& refType = static_cast<const ReferenceType&>(type);

		return (refType.getReferenceTypeName() == this->getReferenceTypeName());
	}


}
