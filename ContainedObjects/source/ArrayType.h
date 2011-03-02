#pragma once

#include "Type.h"
#include <antlr3defs.h>
#include "common_types.h"

namespace COBJ
{
	class ArrayType : public Type
	{
	public:
		ArrayType(const TypePtr& pChildType);
		ArrayType(const pANTLR3_BASE_TREE node);

		~ArrayType(void);

		ast_node_type getASTNodeType() const
		{
			return ASTN_ARRAY_TYPE;
		}

		void getChildNodes(std::list<ASTNodePtr>& children) const;

		const TypePtr& getChildType() const;

		bool operator==(const Type& type) const;

		std::wstring toString() const;

	private:
		TypePtr m_pChildType;
	};
}
