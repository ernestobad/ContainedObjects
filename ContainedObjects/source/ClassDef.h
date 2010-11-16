/*
 * ClassDef.h
 *
 *  Created on: Oct 20, 2010
 *      Author: Ernesto Badillo
 */

#pragma once

#include <antlr3defs.h>
#include "ASTNode.h"
#include "ast_types.h"

namespace COBJ
{
	using namespace std;

	class ClassDef : public ASTNode
	{

	public:
		ClassDef();

		ClassDef(const pANTLR3_BASE_TREE node);

		ast_node_type getASTNodeType() const
		{
			return ASTN_CLASS;
		}

		virtual ~ClassDef();

		const wstring& getClassName() const
		{
			return m_ClassName;
		}

		void setClassName(const wstring& className)
		{
			m_ClassName = className;
		}

		const map<const wstring, FormalParamDefPtr>& getFormalParametersMap() const
		{
			return m_FormalPrametersMap;
		}

		void setFormalParametersMap(const map<const wstring, FormalParamDefPtr>& formalParametersMap)
		{
			m_FormalPrametersMap = formalParametersMap;
		}

		const list<const wstring>& getImplementedInterfaces() const
		{
			return m_ImplementedInterfaces;
		}

		void setImplementedInterfaces(const list<const wstring> implementedInterfaces)
		{
			m_ImplementedInterfaces = implementedInterfaces;
		}

		const list<VariableDeclDefPtr>& getVariableDecls() const
		{
			return m_VariableDecls;
		}

		void setVariableDecls(const list<VariableDeclDefPtr> &variableDecls)
		{
			m_VariableDecls = variableDecls;
		}

		private:
			wstring m_ClassName;
			map<const wstring, FormalParamDefPtr> m_FormalPrametersMap;
			list<const wstring> m_ImplementedInterfaces;
			list<VariableDeclDefPtr> m_VariableDecls;
			bool m_IsNative;
	};
}

