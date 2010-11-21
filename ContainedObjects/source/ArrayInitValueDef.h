#pragma once

#include "ValueDef.h"
#include <antlr3defs.h>
#include "ast_types.h"
#include "common_types.h"

namespace COBJ
{
	class ArrayInitValueDef : public ValueDef
	{
	public:
		ArrayInitValueDef(void);
		ArrayInitValueDef(const pANTLR3_BASE_TREE node);

		virtual ~ArrayInitValueDef(void);

		ast_node_type getASTNodeType() const
		{
			return ASTN_ARRAY_INIT_VALUE;
		}

		void getChildNodes(std::list<ASTNodePtr>& children) const;

		const std::list<ValueDefPtr>& getValues() const
		{
			return m_Values;
		}

		void setValues(const std::list<ValueDefPtr>& values)
		{
			m_Values = values;
		}

		const TypePtr& getDeclaredType() const
		{
			return m_pDeclaredType;
		}

		void setDeclaredType(const TypePtr& pDeclaredType)
		{
			m_pDeclaredType = pDeclaredType;
		}

	private:
		std::list<ValueDefPtr> m_Values;
		TypePtr m_pDeclaredType;
	};
}
