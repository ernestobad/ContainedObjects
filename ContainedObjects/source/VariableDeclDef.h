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
	class Type;
	class ValueDef;

	class VariableDeclDef : public ASTNode
	{

	public:
		VariableDeclDef();
		VariableDeclDef(const pANTLR3_BASE_TREE node);
		virtual ~VariableDeclDef();

		ast_node_type getASTNodeType() const
		{
			return ASTN_VARIABLE;
		}

		bool isStatic() const
		{
			return m_IsStatic;
		}

		void setIsStatic(bool isStatic)
		{
			m_IsStatic = isStatic;
		}

		const ConstTypePtr& getDeclaredType() const
		{
			return m_pDeclaredType;
		}

		void setDeclaredType(const ConstTypePtr& pDeclaredType)
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
		std::wstring m_Name;
		ConstTypePtr m_pDeclaredType;
		ValueDefPtr m_pValue;
	};
}
