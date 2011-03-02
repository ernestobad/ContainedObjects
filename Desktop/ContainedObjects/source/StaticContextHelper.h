#pragma once

#include "static_types.h"
#include "ast_types.h"
#include "common_types.h"

namespace COBJ
{
	using namespace std;

	class StaticContextHelper
	{
	public:

		static void newRootContext(
			StaticContextPtr& pNewCtx,
			const list<ClassDefBasePtr>& classes,
			const LogPtr pLog);

		static void newInstanceContext(
			StaticContextPtr& pNewCtx,
			const ClassDefBasePtr& pClassDefBase,
			const StaticContextPtr& pRootCtx,
			const LogPtr pLog);

		static void newClassContext(
			StaticContextPtr& pNewCtx,
			const ClassDefBasePtr& pClassDefBase,
			const StaticContextPtr& pRootCtx,
			const LogPtr pLog);

	};
}