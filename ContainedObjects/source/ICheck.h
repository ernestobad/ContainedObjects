#pragma once

#include "ast_types.h"
#include "common_types.h"
#include "static_types.h"

namespace COBJ
{
	class ICheck
	{
	public:
		virtual ~ICheck(void) { }

		virtual void doCheck(
			const StaticContextPtr& pCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const = 0;
	};
}