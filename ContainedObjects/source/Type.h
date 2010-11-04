
#pragma once

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
		Type(basic_type basicType);

        virtual ~Type();

		virtual basic_type getBasicType() const;

		virtual bool operator==(const Type& type) const = 0;

		virtual bool operator!=(const Type& type) const;

	private:
		basic_type m_BasicType;
	};
}
