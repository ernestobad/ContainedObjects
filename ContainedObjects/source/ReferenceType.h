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

		ast_node_type getASTNodeType() const
		{
			return ASTN_REFERENCE_TYPE;
		}
		
		void getChildNodes(std::list<ASTNodePtr>& children) const
		{
		}

		reference_type getReferenceType() const;

		const std::wstring& getReferenceTypeName() const;

		bool operator==(const Type& type) const;

		std::wstring toString() const;

	private:
		std::wstring m_ReferenceTypeName;
	};
}
