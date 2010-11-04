/*
 * VariableDeclAssignDef.h
 *
 *  Created on: Oct 21, 2010
 *      Author: Ernesto
 */

#pragma once

class Type;
class ValueDef;

namespace COBJ
{
	class VariableDeclAssignDef {
	public:
		VariableDeclAssignDef();
		virtual ~VariableDeclAssignDef();

		bool isStatic() const
		{
			return m_IsStatic;
		}

		void setIsStatic(bool isStatic)
		{
			m_IsStatic = isStatic;
		}

		const Type* getDeclaredType() const
		{
			return m_pDeclaredType.get();
		}

		void setDeclaredType(boost::shared_ptr<Type>& pDeclaredType)
		{
			m_pDeclaredType = pDeclaredType;
		}

		const std::wstring& getName() const
		{
			return m_Name;
		}

		void setName(const std::wstring& name)
		{
			m_Name = name;
		}

		const boost::shared_ptr<ValueDef>& getValue() const
		{
			return m_pValue;
		}

		void setValue(const boost::shared_ptr<ValueDef>& pValue)
		{
			m_pValue = pValue;
		}

	private:
		bool m_IsStatic;
		boost::shared_ptr<Type> m_pDeclaredType;
		std::wstring m_Name;
		boost::shared_ptr<ValueDef> m_pValue;
	};
}
