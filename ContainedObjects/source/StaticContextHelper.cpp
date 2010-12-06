#include "platform.h"
#include "StaticContextHelper.h"
#include "StaticContextEntry.h"
#include "Context.h"
#include "ClassDef.h"
#include "InterfaceDef.h"
#include "Log.h"
#include "FormalParamDef.h"

namespace COBJ
{
	using namespace std;

	void StaticContextHelper::newRootContext(
			StaticContextPtr& pNewCtx,
			const list<ClassDefBasePtr>& classes,
			const LogPtr pLog)
	{
		StaticContextPtr pCtx(new StaticContext());

		list<ClassDefBasePtr>::const_iterator cit;

		for (cit = classes.begin(); cit != classes.end(); cit++)
		{
			const ClassDefBasePtr pClassDef = *cit;

			StaticContextEntryPtr pEntry(
				pClassDef->getASTNodeType() == ASTN_CLASS ?
				new StaticContextEntry(boost::static_pointer_cast<ClassDef>(pClassDef)) :
				new StaticContextEntry(boost::static_pointer_cast<InterfaceDef>(pClassDef)));

			if (!pCtx->addEntry(pEntry))
			{
				boost::wformat f(L"%1% already exists in context.");
				f % pEntry->getName();
				pLog->log(
					*boost::static_pointer_cast<ASTNode>(pClassDef),
					msg::ErrAnaCtxInit_ClassNameAlreadyExists, f.str());
				continue;
			}
		}

		pNewCtx = boost::static_pointer_cast<StaticContext>(pCtx);
	}

	void StaticContextHelper::newInstanceContext(
		StaticContextPtr& pNewCtx,
		const ClassDefBasePtr& pClassDefBase,
		const StaticContextPtr& pRootCtx,
		const LogPtr pLog)
	{
		pNewCtx = StaticContextPtr(new StaticContext(pRootCtx));

		const map<const wstring, FormalParamDefPtr>& formalParamsMap = pClassDefBase->getFormalParametersMap();

		map<const wstring, FormalParamDefPtr>::const_iterator fpit;

		for (fpit = formalParamsMap.begin(); fpit != formalParamsMap.end(); fpit++)
		{
			const FormalParamDefPtr& pFormalParamDef = (*fpit).second;
			StaticContextEntryPtr pEntry(new StaticContextEntry(pFormalParamDef));
			if (!pNewCtx->addEntry(pEntry))
			{
				boost::wformat f(L"%1% already exists in context.");
				f % pEntry->getName();
				pLog->log(*pFormalParamDef, msg::ErrAnaCtxInit_FParmNameAlreadyExsits, f.str());
				continue;
			}
		}
	}

	void StaticContextHelper::newClassContext(
		StaticContextPtr& pNewCtx,
		const ClassDefBasePtr& pClassDefBase,
		const StaticContextPtr& pRootCtx,
		const LogPtr pLog)
	{
		pNewCtx = StaticContextPtr(new StaticContext(pRootCtx));
	}
}