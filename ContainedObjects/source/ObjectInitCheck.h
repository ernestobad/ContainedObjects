#pragma once

#include "ICheck.h"
#include "ast_types.h"
#include "common_types.h"

namespace COBJ
{
	class ObjectInitCheck : public ICheck
	{
	public:
		ObjectInitCheck(void);
		~ObjectInitCheck(void);

		void doCheck(
			const StaticContextPtr& pRootCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const;

	private:
	};
}
