#pragma once

#include <antlr3defs.h>
#include "ASTNode.h"
#include "ast_types.h"

namespace COBJ
{
	class InterfaceDef : public ASTNode
	{
	public:
		InterfaceDef();
		InterfaceDef(const pANTLR3_BASE_TREE node);

		virtual ~InterfaceDef();

		ast_node_type getASTNodeType() const
		{
			return ASTN_INTERFACE;
		}

		const std::wstring& getIntefaceName() const
		{
			return m_InterfaceName;
		}

		void setInterfaceName(const std::wstring& interfaceName)
		{
			m_InterfaceName = interfaceName;
		}

		const std::list<FormalParamDefPtr>& getFormalParameters() const
		{
			return m_FormalPrameters;
		}

		void setFormalParameters(const std::list<FormalParamDefPtr>& formalParameters)
		{
			m_FormalPrameters = formalParameters;
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
		std::wstring m_InterfaceName;
		std::list<FormalParamDefPtr> m_FormalPrameters;
		std::list<VariableDeclDefPtr> m_VariableDecls;
	};
}
