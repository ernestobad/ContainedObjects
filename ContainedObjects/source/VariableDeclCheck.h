#pragma once

#include "ICheck.h"
#include "static_types.h"
#include "common_types.h"
#include "ast_types.h"

namespace COBJ
{

	class VariableDeclCheck : public ICheck
	{
	public:
		VariableDeclCheck(void);
		~VariableDeclCheck(void);

		void doCheck(
			const StaticContextPtr& pCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const;
	};

}