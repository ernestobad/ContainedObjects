#include "platform.h"
#include "eval.h"
#include "IVariable.h"
#include "IClass.h"
#include "IObject.h"
#include "Context.h"
#include "RuntimeContextEntry.h"
#include "ValueDef.h"
#include "ArrayInitValueDef.h"
#include "FloatLiteralValueDef.h"
#include "IntegerLiteralValueDef.h"
#include "LiteralValueDef.h"
#include "ObjectInitValueDef.h"
#include "ReferencePathValueDef.h"
#include "StringLiteralValueDef.h"
#include "ASTNode.h"
#include "exceptions.h"
#include "ArrayType.h"
#include "Type.h"
#include "ArrayImpl.h"
#include "VariableImpl.h"
#include "ActualParamDef.h"

namespace COBJ
{
	using namespace std;

	void eval(
		const ValueDefPtr& pValueDef,
		const ConstRuntimeContextPtr& pCtx,
		IVariablePtr& pVar)
	{
		switch (pValueDef->getASTNodeType())
		{
		case ASTN_OBJECT_INIT_VALUE:
			{
				ObjectInitValueDefPtr pObjectInitDef
					= boost::static_pointer_cast<ObjectInitValueDef>(pValueDef);

				ConstRuntimeContextEntryPtr pEntry;

				if (!pCtx->lookup(
						pObjectInitDef->getClassName(),
						pEntry))
				{
					throw RuntimeCheckException(L"Class not in context");
				}

				IClassPtr pIClass;

				if (!pEntry->getClass(pIClass))
				{
					throw RuntimeCheckException(L"Context entry is not a class");
				}

				map<const wstring, IVariablePtr> paramsMap;

				map<const wstring, ActualParamDefPtr> paramDefsMap = pObjectInitDef->getActualParamsMap();
				map<const wstring, ActualParamDefPtr>::const_iterator it;

				for (it = paramDefsMap.begin(); it != paramDefsMap.end(); it++)
				{
					const ActualParamDefPtr& pActualParamDef = it->second;
					const ValueDefPtr& pValueDef = pActualParamDef->getValue();

					IVariablePtr pActualParamVar;
					eval(pValueDef, pCtx, pActualParamVar);
					paramsMap[pActualParamDef->getParamName()] = pActualParamVar;
				}

				IObjectPtr pIObject;
				pIClass->newObject(paramsMap, pIObject);

				pVar = IVariablePtr(new VariableImpl(OBJECT_B_TYPE));
				pVar->setObject(pIObject);
				break;
			}
		case ASTN_REFERENCE_PATH_VALUE:
			{
				ReferencePathValueDefPtr pReferencePathDef
					= boost::static_pointer_cast<ReferencePathValueDef>(pValueDef);

				const list<const wstring>& path = pReferencePathDef->getReferencePath();

				list<const wstring>::const_iterator it;
				IVariablePtr pCurrValueVar;

				for (it = path.begin(); it != path.end(); it++)
				{
					const wstring& name = *it;

					if (it == path.begin())
					{
						resolveContextMember(pCtx, name, pCurrValueVar);
					}
					else
					{
						resolveValueMember(pCurrValueVar, name);
					}
				}

				pVar = pCurrValueVar;
				break;
			}
		case ASTN_ARRAY_INIT_VALUE:
			{
				ArrayInitValueDefPtr pArrayInitDef
					= boost::static_pointer_cast<ArrayInitValueDef>(pValueDef);

				const list<ValueDefPtr>& values = pArrayInitDef->getValues();

				ArrayTypePtr pArrayType = 
					boost::static_pointer_cast<ArrayType>(pArrayInitDef->getDeclaredType());

				basic_type basicType = pArrayType->getChildType()->getBasicType();

				IArrayPtr pArray(new ArrayImpl(basicType, values.size()));

				list<ValueDefPtr>::const_iterator it;
				int idx;

				for (it = values.begin(), idx = 0; it != values.end(); it++, idx++)
				{
					const ValueDefPtr& pValueDef = *it;
					IVariablePtr pIVar;
					eval(pValueDef, pCtx, pIVar);
					pArray->assignAt(idx, *pIVar);
				}

				pVar = IVariablePtr(new VariableImpl(ARRAY_B_TYPE));
				pVar->setArray(pArray);
				break;
			}
		case ASTN_STRING_LITERAL_VALUE:
			{
				StringLiteralValueDefPtr pStringDef
					= boost::static_pointer_cast<StringLiteralValueDef>(pValueDef);

				pVar = IVariablePtr(new VariableImpl(STRING_B_TYPE));
				pVar->setString(pStringDef->getStringValue());
				break;
			}
		case ASTN_FLOAT_LITERAL_VALUE:
			{
				FloatLiteralValueDefPtr pFloatDef
					= boost::static_pointer_cast<FloatLiteralValueDef>(pValueDef);

				pVar = IVariablePtr(new VariableImpl(FLOAT_B_TYPE));
				pVar->setFloat(pFloatDef->getFloatValue());
				break;
			}
		case ASTN_INTEGER_LITERAL_VALUE:
			{
				IntegerLiteralValueDefPtr pIntDef
					= boost::static_pointer_cast<IntegerLiteralValueDef>(pValueDef);

				pVar = IVariablePtr(new VariableImpl(INTEGER_B_TYPE));
				pVar->setInteger(pIntDef->getIntValue());
				break;
			}
		default:
			{
				throw InternalErrorException(L"Invalid node type");
			}
		}
	}

	void resolveContextMember(
		const ConstRuntimeContextPtr& pCtx,
		const wstring& name,
		IVariablePtr& pVar)
	{
		ConstRuntimeContextEntryPtr pEntry;
		
		if (!pCtx->lookup(name, pEntry))
		{
			throw RuntimeCheckException(L"Name not found in context");
		}

		switch (pEntry->getType())
		{
		case CLASS_RT_CTX_ENTRY:
			{
				IClassPtr pClass;
				pEntry->getClass(pClass);
				pVar->setClass(pClass);
				break;
			}
		case VARIABLE_RT_CTX_ENTRY:
			{
				IVariablePtr pIVar;
				pEntry->getVariable(pIVar);
				pVar->assign(*pIVar);
				break;
			}
		}
	}

	void resolveValueMember(
		const IVariablePtr& pVar,
		const wstring& name)
	{
		switch (pVar->getBasicType())
		{
		case FLOAT_B_TYPE:
		case INTEGER_B_TYPE:
		case STRING_B_TYPE:
		case ARRAY_B_TYPE:
			{
				throw RuntimeCheckException(L"Unable to resolve member");
			}
		case OBJECT_B_TYPE:
			{
				IObjectPtr pIObj = pVar->getObject();
				pVar->assign(*pIObj->getMemberVariable(name));
				break;
			}
		case CLASS_B_TYPE:
			{
				IClassPtr pIClass = pVar->getClass();
				pVar->assign(*pIClass->getStaticVariable(name));
				break;
			}
		}
	}
}