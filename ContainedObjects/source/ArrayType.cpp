#include "platform.h"
#include "ArrayType.h"

namespace COBJ
{

	ArrayType::ArrayType(const boost::shared_ptr<Type>& pChildType)
		: Type(ARRAY_TYPE), m_pChildType(pChildType)
	{
	}

	ArrayType::~ArrayType(void)
	{
	}

	const Type& ArrayType::getChildType() const
	{
		return *m_pChildType;
	}

	bool ArrayType::operator==(const Type& type) const
	{
		if (type.getBasicType() != this->getBasicType())
		{
			return false;
		}

		const ArrayType& arrayType = static_cast<const ArrayType &>(type);

		const Type& childType1 = arrayType.getChildType();
		const Type& childType2 = getChildType();

		return (childType1 == childType2);
	}
}
