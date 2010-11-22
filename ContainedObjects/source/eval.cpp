#include "platform.h"
#include "eval.h"
#include "IVariable.h"
#include "IClass.h"
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
					throw InternalErrorException(L"Class not in context");
				}

				IClassPtr pIClass;

				if (!pEntry->getClass(pIClass))
				{
					throw InternalErrorException(L"Context entry is not a class");
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

				// TODO:
				// if context is static, first entry must be class or static variable
				// else, all entries are allowed
				// then follow path retrieving member variables with IObject and IClass accessor methods.

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
}