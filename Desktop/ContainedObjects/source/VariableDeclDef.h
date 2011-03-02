/*
 * VariableDeclDef.h
 *
 *  Created on: Oct 21, 2010
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

	class VariableDeclDef : public ASTNode
	{

	public:
		VariableDeclDef();
		VariableDeclDef(const pANTLR3_BASE_TREE node);
		virtual ~VariableDeclDef();

		ast_node_type getASTNodeType() const
		{
			return ASTN_VARIABLE_DECL;
		}

		void getChildNodes(list<ASTNodePtr>& children) const;

		bool isStatic() const
		{
			return m_IsStatic;
		}

		void setIsStatic(bool isStatic)
		{
			m_IsStatic = isStatic;
		}

		const TypePtr& getDeclaredType() const
		{
			return m_pDeclaredType;
		}

		void setDeclaredType(const TypePtr& pDeclaredType)
		{
			m_pDeclaredType = pDeclaredType;
		}

		const wstring& getName() const
		{
			return m_Name;
		}

		void setName(const wstring& name)
		{
			m_Name = name;
		}

		const ValueDefPtr& getValue() const
		{
			return m_pValue;
		}

		void setValue(const ValueDefPtr& pValue)
		{
			m_pValue = pValue;
		}

	private:
		bool m_IsStatic;
		wstring m_Name;
		TypePtr m_pDeclaredType;
		ValueDefPtr m_pValue;
	};
}
