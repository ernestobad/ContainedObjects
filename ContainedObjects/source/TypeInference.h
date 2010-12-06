#pragma once

#include "static_types.h"
#include "ast_types.h"
#include "common_types.h"

namespace COBJ
{
	using namespace std;

	class TypeInference
	{
	public:
		static void inferTypes(
			const list<ClassDefBasePtr>& classes,
			const StaticContextPtr& pRootCtx,
			const LogPtr& pLog);

		static void inferTypes(
			ValueDef& valueDef,
			StaticContextPtr& pClassCtx,
			const LogPtr& pLog);

	private:
		static bool followPathElement(
			const Type& currentType,
			const StaticContext& rootCtx,
			const wstring& pathElement,
			TypePtr& pNextType);
	};
}