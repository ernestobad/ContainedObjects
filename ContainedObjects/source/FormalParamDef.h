/*
 * FormalParamDef.h
 *
 *  Created on: Oct 20, 2010
 *      Author: Ernesto
 */

#pragma once

#include <antlr3defs.h>
#include "ASTNode.h"
#include "ast_types.h"
#include "common_types.h"

namespace COBJ
{
	using namespace std;

	class FormalParamDef : public ASTNode
	{
	public:
		FormalParamDef();
		FormalParamDef(const pANTLR3_BASE_TREE node);

		virtual ~FormalParamDef();

		ast_node_type getASTNodeType() const
		{
			return ASTN_FORMAL_PARAM;
		}

		void getChildNodes(list<ASTNodePtr>& children) const;

		const TypePtr& getType() const
		{
			return m_pType;
		}

		void setType(const TypePtr& pType)
		{
			m_pType = pType;
		}

		const std::wstring& getParamName() const
		{
			return m_ParamName;
		}

		void setParamName(const std::wstring& paramName)
		{
			m_ParamName = paramName;
		}

	private:
		TypePtr m_pType;
		wstring m_ParamName;
	};
}
