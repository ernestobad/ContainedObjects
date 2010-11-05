#pragma once

#include <antlr3defs.h>

namespace COBJ
{
	class Type;

	class VariableDeclDef
	{
	public:
		VariableDeclDef(void);
		VariableDeclDef(const pANTLR3_BASE_TREE node);
		virtual ~VariableDeclDef(void);

		bool isStatic() const
		{
			return m_IsStatic;
		}

		void setIsStatic(bool isStatic)
		{
			m_IsStatic = isStatic;
		}

		const boost::shared_ptr<Type>& getDeclaredType() const
		{
			return m_pDeclaredType;
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

	private:
		bool m_IsStatic;
		boost::shared_ptr<Type> m_pDeclaredType;
		std::wstring m_Name;
	};
}