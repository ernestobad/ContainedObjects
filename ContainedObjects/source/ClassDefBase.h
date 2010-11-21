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

		virtual const wstring& getClassName() const = 0;

		virtual void setClassName(const wstring& className) = 0;

		virtual const map<const wstring, FormalParamDefPtr>& getFormalParametersMap() const = 0;

		virtual void setFormalParametersMap(const map<const wstring, FormalParamDefPtr>& formalParametersMap) = 0;

		virtual const list<VariableDeclDefPtr>& getVariableDecls() const = 0;

		virtual void setVariableDecls(const list<VariableDeclDefPtr> &variableDecls) = 0;
	};
}