#pragma once

#include "ValueDef.h"
#include <antlr3defs.h>



namespace COBJ
{
	class Type;

	class ArrayInitValueDef : public ValueDef
	{
	public:
		ArrayInitValueDef(void);
		ArrayInitValueDef(const pANTLR3_BASE_TREE node);

		virtual ~ArrayInitValueDef(void);

		const std::list<boost::shared_ptr<ValueDef>>& getValues() const
		{
			return m_Values;
		}

		void setValues(const std::list<boost::shared_ptr<ValueDef>>& values)
		{
			m_Values = values;
		}

		const boost::shared_ptr<Type>& getDeclaredType() const
		{
			return m_pDeclaredType;
		}

		void setDeclaredType(const boost::shared_ptr<Type>& pDeclaredType)
		{
			m_pDeclaredType = pDeclaredType;
		}

	private:
		std::list<boost::shared_ptr<ValueDef>> m_Values;
		boost::shared_ptr<Type> m_pDeclaredType;
	};

}
