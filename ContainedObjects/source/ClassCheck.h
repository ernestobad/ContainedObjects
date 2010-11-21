#pragma once

#include "ICheck.h"
#include "static_types.h"
#include "common_types.h"
#include "ast_types.h"

namespace COBJ
{

	class ClassCheck : public ICheck
	{
	public:
		ClassCheck(void);
		~ClassCheck(void);

		void doCheck(
			const ConstStaticContextPtr& pCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const;

	private:
		void checkInterfaceParams(
			const ClassDefPtr& pClassDef,
			const InterfaceDefPtr& pInterfaceDef,
			const ConstStaticContextPtr& pCtx,
			const LogPtr& pLog) const;

		void checkInterfaceVars(
			const ClassDefPtr& pClassDef,
			const InterfaceDefPtr& pInterfaceDef,
			const ConstStaticContextPtr& pCtx,
			const LogPtr& pLog) const;
	};

}
