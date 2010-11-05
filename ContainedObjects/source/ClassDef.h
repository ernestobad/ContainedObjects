/*
 * ClassDef.h
 *
 *  Created on: Oct 20, 2010
 *      Author: Ernesto Badillo
 */

#pragma once

#include <antlr3defs.h>

namespace COBJ
{
	class FormalParamDef;
	class VariableDeclAssignDef;

	class ClassDef {

	public:
		ClassDef();

		ClassDef(const pANTLR3_BASE_TREE node);

		virtual ~ClassDef();

		const std::wstring& getClassName() const
		{
			return m_ClassName;
		}

		void setClassName(const std::wstring& className)
		{
			m_ClassName = className;
		}

		const std::list<boost::shared_ptr<FormalParamDef>>& getFormalParameters() const
		{
			return m_FormalPrameters;
		}

		void setFormalParameters(const std::list<boost::shared_ptr<FormalParamDef>>& formalParameters)
		{
			m_FormalPrameters = formalParameters;
		}

		const std::list<std::wstring>& getImplementedInterfaces()
		{
			return m_ImplementedInterfaces;
		}

		void setImplementedInterfaces(const std::list<std::wstring> implementedInterfaces)
		{
			m_ImplementedInterfaces = implementedInterfaces;
		}

		const std::list<boost::shared_ptr<VariableDeclAssignDef>>& getVariableDecls() const
		{
			return m_VariableDecls;
		}

		void setVariableDecls(const std::list<boost::shared_ptr<VariableDeclAssignDef>> &variableDecls)
		{
			m_VariableDecls = variableDecls;
		}

		private:
			std::wstring m_ClassName;
			std::list<boost::shared_ptr<FormalParamDef>> m_FormalPrameters;
			std::list<std::wstring> m_ImplementedInterfaces;
			std::list<boost::shared_ptr<COBJ::VariableDeclAssignDef>> m_VariableDecls;
			bool m_IsNative;
	};

}

