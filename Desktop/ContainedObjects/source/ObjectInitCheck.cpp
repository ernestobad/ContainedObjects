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
#include "message_code.h"

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
		const StaticContextPtr& pRootCtx,
		const ASTNodePtr& pNode,
		const LogPtr& pLog) const
	{
		if (pNode->getASTNodeType() != ASTN_OBJECT_INIT_VALUE)
			return;

		const ObjectInitValueDefPtr pObjectInit = 
			boost::static_pointer_cast<ObjectInitValueDef>(pNode);

		const wstring& className = pObjectInit->getClassName();

		CStaticContextEntryPtr pContextEntry;
		if (!pRootCtx->lookup(className, pContextEntry))
		{
			boost::wformat f(L"Can't find name %1% in context.");
			f % className;
			pLog->log(*pNode, msg::ErrAnaObjInit_ClassNotFound, f.str());
			return;
		}

		ClassDefPtr pClass;
		if (!pContextEntry->getClass(pClass))
		{
			boost::wformat f(L"%1% is not a class.");
			f % className;
			pLog->log(*pNode, msg::ErrAnaObjInit_NotAClass, f.str());
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
				pLog->log(*pObjectInit, msg::ErrAnaObjInit_MissingParam, f.str());
			}
		}

		map<const wstring, ActualParamDefPtr>::const_iterator apIt;
		for (apIt = actualParamsMap.begin(); apIt != actualParamsMap.end(); apIt++)
		{
			const wstring& actualParamName = (*apIt).first;
			const ActualParamDefPtr& pActualParamDef = (*apIt).second;

			const TypePtr& pActualParamInferredType = 
				pActualParamDef->getValue()->getInferredType();

			if ((fpIt = formalParamsMap.find(actualParamName)) == formalParamsMap.end())
			{
				boost::wformat f(L"Unkown parameter %1%.");
				f % actualParamName;
				pLog->log(*pActualParamDef, msg::ErrAnaObjInit_UnknownParam, f.str());
				continue;
			}

			if (pActualParamDef->getValue()->getInferredType().get() == NULL)
			{
				// type inference should've failed
				assert(pLog->hasMessages(msg::ERR|msg::ANALYSIS|msg::TYPE_INFER));
				continue;
			}

			const FormalParamDefPtr& pFormalParamDef = (*fpIt).second;

			const TypePtr& pFormalParamType = pFormalParamDef->getType();

			if (!SemanticAnalysis::isTypeAssignableFrom(
					 pFormalParamType,
					pActualParamInferredType,
					pRootCtx))
			{
				boost::wformat f(L"Cannot convert value from %1% to %2%.");
				f % pActualParamInferredType->toString() %  pFormalParamType->toString();
				pLog->log(*pActualParamDef, msg::ErrAnaObjInit_IncompTypes, f.str());
				continue;
			}
		}
		
	}
}