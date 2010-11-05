#pragma once

#include <antlr3defs.h>

namespace COBJ
{
	class FormalParamDef;
	class VariableDeclDef;

	class InterfaceDef
	{
	public:
		InterfaceDef();
		InterfaceDef(const pANTLR3_BASE_TREE node);

		virtual ~InterfaceDef();

		const std::wstring& getIntefaceName() const
		{
			return m_InterfaceName;
		}

		void setInterfaceName(const std::wstring& interfaceName)
		{
			m_InterfaceName = interfaceName;
		}

		const std::list<boost::shared_ptr<FormalParamDef>>& getFormalParameters() const
		{
			return m_FormalPrameters;
		}

		void setFormalParameters(const std::list<boost::shared_ptr<FormalParamDef>>& formalParameters)
		{
			m_FormalPrameters = formalParameters;
		}

		const std::list<boost::shared_ptr<VariableDeclDef>>& getVariableDecls() const
		{
			return m_VariableDecls;
		}

		void setVariableDecls(const std::list<boost::shared_ptr<VariableDeclDef>> &variableDecls)
		{
			m_VariableDecls = variableDecls;
		}

	private:
		std::wstring m_InterfaceName;
		std::list<boost::shared_ptr<FormalParamDef>> m_FormalPrameters;
		std::list<boost::shared_ptr<VariableDeclDef>> m_VariableDecls;
	};
}
