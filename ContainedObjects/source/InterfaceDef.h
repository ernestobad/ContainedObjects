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

		void getChildNodes(list<ASTNodePtr>& children) const;
	};
}
