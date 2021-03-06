
#pragma once

#include "ASTNode.h"
#include "common_types.h"
#include <antlr3defs.h>

namespace COBJ
{
	enum basic_type {
		FLOAT_B_TYPE,
		INTEGER_B_TYPE,
		STRING_B_TYPE,
		ARRAY_B_TYPE,
		OBJECT_B_TYPE,
		CLASS_B_TYPE
	};

	class Type : public ASTNode
	{
	public:
		Type(basic_type basicType);
		Type(basic_type basicType, const pANTLR3_BASE_TREE node);

        virtual ~Type();

		virtual basic_type getBasicType() const;

		virtual bool operator==(const Type& type) const = 0;

		virtual bool operator!=(const Type& type) const;

		virtual std::wstring toString() const = 0;

	protected:
		basic_type m_BasicType;
	};

	void createType(
			const pANTLR3_BASE_TREE node,
			TypePtr& pType);

	void createSimpleType(
				const pANTLR3_BASE_TREE node,
				TypePtr& pType);
}
