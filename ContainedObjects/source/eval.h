#pragma once

#include "ast_types.h"
#include "runtime_types.h"

namespace COBJ
{
	void eval(
		const ValueDefPtr& pValueDef,
		const ConstRuntimeContextPtr& pCtx,
		IVariablePtr& pVar);
}