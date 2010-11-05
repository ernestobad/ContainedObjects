
#pragma once

#include <antlr3defs.h>

namespace COBJ
{
	enum basic_type {
		FLOAT_TYPE,
		INTEGER_TYPE,
		STRING_TYPE,
		ARRAY_TYPE,
		OBJECT_TYPE,
		CLASS_TYPE
	};

	class Type
	{
	public:
		Type(void);
		Type(basic_type basicType);

        virtual ~Type();

		virtual basic_type getBasicType() const;

		virtual bool operator==(const Type& type) const = 0;

		virtual bool operator!=(const Type& type) const;

	protected:
		basic_type m_BasicType;
	};

	void createType(
			const pANTLR3_BASE_TREE node,
			boost::shared_ptr<Type>& pType);

	void createSimpleType(
				const pANTLR3_BASE_TREE node,
				boost::shared_ptr<Type>& pType);
}
