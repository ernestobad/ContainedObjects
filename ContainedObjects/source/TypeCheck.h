#pragma once

#include "common_types.h"
#include "static_types.h"
#include "ast_types.h"
#include "ICheck.h"

namespace COBJ
{
	class TypeCheck : public ICheck
	{
	public:
		TypeCheck(void);
		~TypeCheck(void);

		void doCheck(
			const ConstStaticContextPtr& pCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const;
	};
}