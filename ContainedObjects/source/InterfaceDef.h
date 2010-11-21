#pragma once

#include <antlr3defs.h>
#include "ASTNode.h"
#include "ast_types.h"
#include "ClassDefBase.h"

namespace COBJ
{
	using namespace std;

	class InterfaceDef : public ClassDefBase
	{
	public:
		InterfaceDef();
		InterfaceDef(const pANTLR3_BASE_TREE node);

		virtual ~InterfaceDef();

		ast_node_type getASTNodeType() const
		{
			return ASTN_INTERFACE;
		}

		void getChildNodes(std::list<ASTNodePtr>& children) const;

		const std::wstring& getClassName() const
		{
			return m_ClassName;
		}

		void setClassName(const std::wstring& className)
		{
			m_ClassName = className;
		}

		const map<const wstring, FormalParamDefPtr>& getFormalParametersMap() const
		{
			return m_FormalParametersMap;
		}

		void setFormalParametersMap(const map<const wstring, FormalParamDefPtr>& formalParametersMap)
		{
			m_FormalParametersMap = formalParametersMap;
		}

		const std::list<VariableDeclDefPtr>& getVariableDecls() const
		{
			return m_VariableDecls;
		}

		void setVariableDecls(const std::list<VariableDeclDefPtr> &variableDecls)
		{
			m_VariableDecls = variableDecls;
		}

	private:
		wstring m_ClassName;
		map<const wstring, FormalParamDefPtr> m_FormalParametersMap;
		list<VariableDeclDefPtr> m_VariableDecls;
	};
}
