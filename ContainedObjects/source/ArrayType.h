#pragma once

#include "Type.h"

namespace COBJ
{
	class ArrayType : public Type
	{
	public:
		ArrayType(const boost::shared_ptr<Type>& pChildType);

		~ArrayType(void);

		const Type& getChildType() const;

		bool operator==(const Type& type) const;

	private:
		boost::shared_ptr<Type> m_pChildType;
	};
}
