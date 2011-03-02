#pragma once

#include "runtime_types.h"

namespace COBJ
{
	using namespace std;

	class RuntimeContextHelper
	{
	public:
		static void newRootContext(
			RuntimeContextPtr& pRootCtx,
			const list<IClassPtr>& classes);

		static void newClassContext(
			RuntimeContextPtr& pClassCtx,
			const RuntimeContextPtr& pRootCtx);

		static void newInstanceContext(
			RuntimeContextPtr& pInstanceCtx,
			const map<const wstring, IVariablePtr> params,
			const RuntimeContextPtr& pClassCtx);
	};
}