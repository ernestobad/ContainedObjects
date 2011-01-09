#pragma once

#include "ICheck.h"
#include "static_types.h"
#include "ast_types.h"
#include "common_types.h"

namespace COBJ
{
	class ArrayInitCheck : public ICheck
	{
	public:
		ArrayInitCheck(void);
		~ArrayInitCheck(void);

		void doCheck(
			const StaticContextPtr& pRootCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const;
	};
}