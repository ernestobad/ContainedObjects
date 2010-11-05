#pragma once

#include "Type.h"
#include <antlr3defs.h>

namespace COBJ
{
	class ArrayType : public Type
	{
	public:
		ArrayType(const boost::shared_ptr<Type>& pChildType);
		ArrayType(const pANTLR3_BASE_TREE node);

		~ArrayType(void);

		const Type& getChildType() const;

		bool operator==(const Type& type) const;

	private:
		boost::shared_ptr<Type> m_pChildType;
	};
}
