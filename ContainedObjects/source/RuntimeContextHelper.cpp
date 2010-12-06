#include "platform.h"
#include "RuntimeContextHelper.h"
#include "Context.h"
#include "RuntimeContextEntry.h"
#include "IClass.h"
#include "IVariable.h"

namespace COBJ
{
	void RuntimeContextHelper::newRootContext(
		RuntimeContextPtr& pRootCtx,
		const list<IClassPtr>& classes)
	{
		pRootCtx = RuntimeContextPtr(new RuntimeContext());

		list<IClassPtr>::const_iterator it;

		for (it = classes.begin(); it != classes.end(); it++)
		{
			const IClassPtr& pIClass = *it;
			RuntimeContextEntryPtr pEntry(new RuntimeContextEntry(pIClass));
			pRootCtx->addEntry(pEntry);
		}
	}

	void RuntimeContextHelper::newClassContext(
		RuntimeContextPtr& pClassCtx,
		const RuntimeContextPtr& pRootCtx)
	{
		pClassCtx = RuntimeContextPtr(new RuntimeContext());
	}

	void RuntimeContextHelper::newInstanceContext(
		RuntimeContextPtr& pInstanceCtx,
		const map<const wstring, IVariablePtr> params,
		const RuntimeContextPtr& pClassCtx)
	{
		pInstanceCtx = RuntimeContextPtr(new RuntimeContext());

		map<const wstring, IVariablePtr>::const_iterator it;

		for (it = params.begin(); it != params.end(); it++)
		{
			const wstring& name = it->first;
			const IVariablePtr& pVar = it->second;
			RuntimeContextEntryPtr pEntry(new RuntimeContextEntry(name, pVar));
			pInstanceCtx->addEntry(pEntry);
		}
	}
}