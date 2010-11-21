#pragma once

#include "ICheck.h"
#include "static_types.h"
#include "common_types.h"
#include "ast_types.h"

namespace COBJ
{
	class InterfaceCheck : public ICheck
	{
	public:
		InterfaceCheck(void);
		~InterfaceCheck(void);

		void doCheck(
			const ConstStaticContextPtr& pCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const;
	};
}