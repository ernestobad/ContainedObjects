/*
 * ValueDef.h
 *
 *  Created on: Oct 21, 2010
 *      Author: Ernesto
 */

#pragma once

class Type;

namespace COBJ {

	enum value_type
	{
		OBJECT_INIT, ARRAY_INIT, LITERAL, REFERENCE_PATH
	};

	class ValueDef {
	public:
		ValueDef();
		virtual ~ValueDef();

		const boost::shared_ptr<Type>& getInferredType() const
		{
			return m_pInferredType;
		}

		void setInferredType(boost::shared_ptr<Type>& pInferredType)
		{
			m_pInferredType = pInferredType;
		}

		value_type getValueType() const
		{
			return m_ValueType;
		}

		void setValueType(const value_type valueType)
		{
			m_ValueType = valueType;
		}

	private:
		boost::shared_ptr<Type> m_pInferredType;
		value_type m_ValueType;

	};

}
