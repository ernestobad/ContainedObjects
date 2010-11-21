/*
 * ActualParamDef.h
 *
 *  Created on: Oct 22, 2010
 *      Author: Ernesto
 */

#pragma once

#include <antlr3defs.h>
#include "ASTNode.h"
#include "ast_types.h"

namespace COBJ
{
	class ValueDef;

	class ActualParamDef : public ASTNode
	{
	public:
		ActualParamDef();
		ActualParamDef(const pANTLR3_BASE_TREE node);

		virtual ~ActualParamDef();

		ast_node_type getASTNodeType() const
		{
			return ASTN_ACTUAL_PARAM;
		}

		void getChildNodes(std::list<ASTNodePtr>& children) const;

		const std::wstring& getParamName() const
		{
			return m_ParamName;
		}

		void setParamName(const std::wstring& paramName)
		{
			m_ParamName = paramName;
		}

		const ValueDefPtr& getValue() const
		{
			return m_pValue;
		}

		void setValue(ValueDefPtr& pValue)
		{
			m_pValue = pValue;
		}

	private:
		std::wstring m_ParamName;
		ValueDefPtr m_pValue;
	};
}
