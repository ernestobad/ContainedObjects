#pragma once

#include "ast_types.h"
#include "runtime_types.h"

namespace COBJ
{
	using namespace std;

	void eval(
		const ValueDefPtr& pValueDef,
		const ConstRuntimeContextPtr& pCtx,
		IVariablePtr& pVar);

	void resolveContextMember(
		const ConstRuntimeContextPtr& pCtx,
		const wstring& name,
		IVariablePtr& pMemberVar);

	void resolveValueMember(
		const IVariablePtr& pIVar,
		const wstring& name,
		IVariablePtr& pMemberVar);
}