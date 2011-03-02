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
#include "ClassDefBase.h"

namespace COBJ
{
	using namespace std;

	class ClassDef : public ClassDefBase
	{

	public:
		ClassDef();

		ClassDef(const pANTLR3_BASE_TREE node);

		ast_node_type getASTNodeType() const
		{
			return ASTN_CLASS; 
		}

		void getChildNodes(list<ASTNodePtr>& children) const;

		~ClassDef();

	private:
		set<const wstring> dependencies;
	};
}

