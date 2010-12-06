#pragma once

#include "ast_types.h"
#include "ASTNode.h"

namespace COBJ
{
	using namespace std;

	class ClassDefBase : public ASTNode
	{
	public:

		ClassDefBase()
			: ASTNode()
		{
		}

		ClassDefBase(const pANTLR3_BASE_TREE node)
			: ASTNode(node)
		{
		}

        virtual ~ClassDefBase()
		{
		}

		virtual ast_node_type getASTNodeType() const = 0;

		virtual const wstring& getClassName() const
		{
			return m_ClassName;
		}

		virtual void setClassName(const wstring& className)
		{
			m_ClassName = className;
		}

		virtual const map<const wstring, FormalParamDefPtr>& getFormalParametersMap() const
		{
			return m_FormalParametersMap;
		}

		virtual void setFormalParametersMap(const map<const wstring, FormalParamDefPtr>& formalParametersMap)
		{
			m_FormalParametersMap = formalParametersMap;
		}

		virtual const list<const wstring>& getImplementedInterfaces() const
		{
			return m_ImplementedInterfaces;
		}

		virtual void setImplementedInterfaces(const list<const wstring>& implementedInterfaces)
		{
			m_ImplementedInterfaces = implementedInterfaces;
		}

		virtual const list<VariableDeclDefPtr>& getVariableDecls() const
		{
			return m_VariableDecls;
		}

		virtual void setVariableDecls(const list<VariableDeclDefPtr> &variableDecls)
		{
			m_VariableDecls = variableDecls;
		}

		virtual const set<const wstring>& getStaticDependencies() const
		{
			return dependencies;
		}

		virtual void addStaticDependency(const wstring& className)
		{
			dependencies.insert(className);
		}

	protected:
		wstring m_ClassName;
		map<const wstring, FormalParamDefPtr> m_FormalParametersMap;
		list<const wstring> m_ImplementedInterfaces;
		list<VariableDeclDefPtr> m_VariableDecls;
		set<const wstring> dependencies;
	};
}