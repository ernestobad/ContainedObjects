#include "platform.h"
#include "ObjectInitCheck.h"
#include "Log.h"
#include "ASTNode.h"
#include "ValueDef.h"
#include "ObjectInitValueDef.h"
#include "Context.h"
#include "StaticContextEntry.h"
#include "ClassDef.h"
#include "ActualParamDef.h"
#include "FormalParamDef.h"
#include "SemanticAnalysis.h"

namespace COBJ
{
	using namespace std;

	ObjectInitCheck::ObjectInitCheck(void)
	{
	}

	ObjectInitCheck::~ObjectInitCheck(void)
	{
	}

	void ObjectInitCheck::doCheck(
		const ConstStaticContextPtr& pCtx,
		const ConstASTNodePtr& pNode,
		const LogPtr& pLog) const
	{
		if (pNode->getASTNodeType() != ASTN_OBJECT_INIT_VALUE)
			return;

		const ConstObjectInitValueDefPtr pObjectInit = 
			boost::static_pointer_cast<const ObjectInitValueDef>(pNode);

		const wstring& className = pObjectInit->getClassName();

		ConstStaticContextEntryPtr pContextEntry;
		if (!pCtx->lookup(className, pContextEntry))
		{
			boost::wformat f(L"Can't find name %1% in context.");
			f % className;
			pLog->addError(*pNode, f.str());
			return;
		}

		ClassDefPtr pClass;
		if (!pContextEntry->getClass(pClass))
		{
			boost::wformat f(L"%1% is not a class.");
			f % className;
			pLog->addError(*pNode, f.str());
			return;
		}

		const map<const wstring, FormalParamDefPtr>& formalParamsMap = pClass->getFormalParametersMap();
		const map<const wstring, ActualParamDefPtr>& actualParamsMap = pObjectInit->getActualParamsMap();

		map<const wstring, FormalParamDefPtr>::const_iterator fpIt;
		for (fpIt = formalParamsMap.begin(); fpIt != formalParamsMap.end(); fpIt++)
		{
			const wstring& formalParamName = (*fpIt).first;
			
			if (actualParamsMap.find(formalParamName) == actualParamsMap.end())
			{
				boost::wformat f(L"Missing parameter %1%.");
				f % formalParamName;
				pLog->addError(*pObjectInit, f.str());
			}
		}

		map<const wstring, ActualParamDefPtr>::const_iterator apIt;
		for (apIt = actualParamsMap.begin(); apIt != actualParamsMap.end(); apIt++)
		{
			const wstring& actualParamName = (*apIt).first;
			ActualParamDefPtr& pActualParamDef = (*apIt).second;

			if ((fpIt = formalParamsMap.find(actualParamName)) == formalParamsMap.end())
			{
				boost::wformat f(L"Unkown parameter %1%.");
				f % actualParamName;
				pLog->addError(*pActualParamDef, f.str());
			}

			FormalParamDefPtr& pFormalParamDef = (*fpIt).second;

			// TODO:
			SemanticAnalysis::isTypeAssignableFrom
		}
		
	}
}