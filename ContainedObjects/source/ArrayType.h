#pragma once

#include "Type.h"
#include <antlr3defs.h>
#include "common_types.h"

namespace COBJ
{
	class ArrayType : public Type
	{
	public:
		ArrayType(const ConstTypePtr& pChildType);
		ArrayType(const pANTLR3_BASE_TREE node);

		~ArrayType(void);

		const ConstTypePtr& getChildType() const;

		bool operator==(const Type& type) const;

		std::wstring toString() const;

	private:
		ConstTypePtr m_pChildType;
	};
}
