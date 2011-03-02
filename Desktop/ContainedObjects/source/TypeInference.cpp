#include "platform.h"
#include "TypeInference.h"
#include "ClassDefBase.h"
#include "StaticContextEntry.h"
#include "Context.h"
#include "VariableDeclDef.h"
#include "ValueDef.h"
#include "ObjectInitValueDef.h"
#include "Type.h"
#include "ReferenceType.h"
#include "ActualParamDef.h"
#include "ArrayInitValueDef.h"
#include "LiteralValueDef.h"
#include "ReferencePathValueDef.h"
#include "FormalParamDef.h"
#include "ClassDef.h"
#include "InterfaceDef.h"
#include "PrimitiveType.h"
#include "Log.h"
#include "StaticContextHelper.h"

namespace COBJ
{

	void TypeInference::inferTypes(
			const list<ClassDefBasePtr>& classes,
			const StaticContextPtr& pRootCtx,
			const LogPtr& pLog)
	{
		list<ClassDefBasePtr>::const_iterator cit;

		for (cit = classes.begin(); cit != classes.end(); cit++)
		{
			const ClassDefBasePtr& pClassDefBase = *cit;

			if (pClassDefBase->getASTNodeType() == ASTN_INTERFACE)
			{
				continue;
			}

			StaticContextPtr pClassCtx;
			StaticContextHelper::newClassContext(pClassCtx, pClassDefBase, pRootCtx, pLog);

			StaticContextPtr pInstanceCtx;
			StaticContextHelper::newInstanceContext(pInstanceCtx, pClassDefBase, pRootCtx, pLog);

			const list<VariableDeclDefPtr>& variables = pClassDefBase->getVariableDecls();

			list<VariableDeclDefPtr>::const_iterator vit;

			for (vit = variables.begin(); vit != variables.end(); vit++)
			{
				const VariableDeclDefPtr& pVariable = *vit;
				const ValueDefPtr& pValueDef = pVariable->getValue();

				if (pValueDef.get() == NULL)
				{
					// this is reported by ClassCheck
					continue;
				}

				StaticContextPtr& pParentCtx = (pVariable->isStatic() ? pClassCtx : pInstanceCtx);

				StaticContextPtr pMemberCtx(new StaticContext(pParentCtx, pVariable->isStatic()));
				
				inferTypes(*pValueDef, pMemberCtx, pLog);

				StaticContextEntryPtr pEntry(new StaticContextEntry(pVariable));
				pParentCtx->addEntry(pEntry);
			}
		}
	}

	void TypeInference::inferTypes(
		ValueDef& valueDef,
		StaticContextPtr& pMemberCtx,
		const LogPtr& pLog)
	{
		switch (valueDef.getValueType())
		{
		case OBJECT_INIT:
			{
				const ObjectInitValueDef& objectInitDef = static_cast<const ObjectInitValueDef&>(valueDef);

				TypePtr pType = TypePtr(
					new ReferenceType(OBJECT_REF_TYPE, objectInitDef.getClassName()));

				valueDef.setInferredType(pType);

				const map<const wstring, ActualParamDefPtr>& actualParamsMap = objectInitDef.getActualParamsMap();

				map<const wstring, ActualParamDefPtr>::const_iterator it;

				for (it = actualParamsMap.begin(); it != actualParamsMap.end(); it++)
				{
					const ActualParamDefPtr& pActualParamDef = (*it).second;
					const ValueDefPtr& pParamValueDef = pActualParamDef->getValue();

					inferTypes(*pParamValueDef, pMemberCtx, pLog);
				}
			}
			break;
		case ARRAY_INIT:
			{
				const ArrayInitValueDef& arrayInitDef = static_cast<const ArrayInitValueDef&>(valueDef);

				valueDef.setInferredType(arrayInitDef.getDeclaredType());

				const list<ValueDefPtr>& arrayValues = arrayInitDef.getValues();

				list<ValueDefPtr>::const_iterator it;

				for (it = arrayValues.begin(); it != arrayValues.end(); it++)
				{
					const ValueDefPtr& pArrayValue = *it;

					inferTypes(*pArrayValue, pMemberCtx, pLog);
				}
			}
			break;
		case LITERAL:
			{
				const LiteralValueDef& literalDef = static_cast<const LiteralValueDef&>(valueDef);

				switch (literalDef.getLiteralType())
				{
				case INTEGER_LITERAL:
					valueDef.setInferredType(P_INTEGER_TYPE);
					break;
				case FLOAT_LITERAL:
					valueDef.setInferredType(P_FLOAT_TYPE);
					break;
				case STRING_LITERAL:
					valueDef.setInferredType(P_STRING_TYPE);
					break;
				default:
					assert(false);
					break;
				}
			}
			break;
		case REFERENCE_PATH:
			{
				const ReferencePathValueDef& referencePathDef = static_cast<const ReferencePathValueDef&>(valueDef);

				const list<const wstring>& path = referencePathDef.getReferencePath();

				StaticContextEntryPtr pEntry;

				TypePtr pCurrentType;

				list<const wstring>::const_iterator it;

				wstring parentPath(L"");

				for (it = path.begin(); it != path.end(); it++)
				{
					const wstring& pathElement = *it;

					if (it == path.begin())
					{
						CStaticContextEntryPtr pEntry;

						if (!pMemberCtx->lookup(pathElement, pEntry))
						{
							boost::wformat f(L"Unable to resolve name %1%");
							f % pathElement;
							pLog->log(referencePathDef, msg::ErrAnaTypeInfer_NameNotInContext, f.str());
							return;
						}
						else
						{
							switch (pEntry->getStaticEntryType())
							{
							case CLASS_DEF_CTX_ENTRY:
								{
									TypePtr pType(new ReferenceType(CLASS_REF_TYPE, pEntry->getName()));
									pCurrentType = pType;
								}
								break;
							case INTERFACE_DEF_CTX_ENTRY:
								{
									TypePtr pType(new ReferenceType(CLASS_REF_TYPE, pEntry->getName()));
									pCurrentType = pType;
								}
								break;
							case VARIABLE_DEF_CTX_ENTRY:
								{
									VariableDeclDefPtr pVariableDef;
									pEntry->getVariable(pVariableDef);

									if (pMemberCtx->isStatic() && !pVariableDef->isStatic())
									{
										boost::wformat f(L"Cannot refer to a non static variable from an static context: %1%");
										f % pathElement;
										pLog->log(referencePathDef, msg::ErrAnaTypeInfer_NonStaticVarRef, f.str());
										return;
									}
									else
									{
										pCurrentType = pVariableDef->getDeclaredType();
									}
								}
								break;
							case FORMAL_PARAM_DEF_CTX_ENTRY:
								{
									if (pMemberCtx->isStatic())
									{
										boost::wformat f(L"Cannot refer to a class parameter from an static context: %1%");
										f % pathElement;
										pLog->log(referencePathDef, msg::ErrAnaTypeInfer_NonStaticParamRef, f.str());
										return;
									}

									FormalParamDefPtr pFormalParamDef;
									pEntry->getFormalParam(pFormalParamDef);
									pCurrentType = pFormalParamDef->getType();
								}
								break;
							default:
								assert(false);
								return;
							}
						}
					}
					else
					{
						assert(pCurrentType.get() != NULL);

						StaticContextPtr pRootCtx;
						pMemberCtx->getRootContext(pRootCtx);

						if (!followPathElement(
								*pCurrentType,
								*pRootCtx,
								pathElement,
								pCurrentType))
						{
							boost::wformat f(L"%1% is not a member of %2%");
							f % pathElement % parentPath;
							pLog->log(referencePathDef, msg::ErrAnaTypeInfer_NotAMember, f.str());
							return;
						}
					}

					if (parentPath.size())
					{
						parentPath.append(L".");
					}

					parentPath.append(pathElement);
				}

				assert(pCurrentType.get() != NULL);

				valueDef.setInferredType(pCurrentType);
			}
			break;
		default:
			assert(false);
			break;
		}
	}

	bool TypeInference::followPathElement(
			const Type& currentType,
			const StaticContext& rootCtx,
			const wstring& pathElement,
			TypePtr& pNextType)
	{
		boolean isObject = false;
		switch (currentType.getBasicType())
		{
		case FLOAT_B_TYPE:
		case INTEGER_B_TYPE:
		case STRING_B_TYPE:
		case ARRAY_B_TYPE:
			{
				return false;
			}
		case OBJECT_B_TYPE:
		case CLASS_B_TYPE:
			{
				const ReferenceType& refType = static_cast<const ReferenceType&>(currentType);
				const wstring& className = refType.getReferenceTypeName();

				CStaticContextEntryPtr pEntry;

				if (!rootCtx.lookup(className, pEntry))
				{
					return false;
				}

				list<VariableDeclDefPtr> varsDecls;

				if (pEntry->getStaticEntryType() == CLASS_DEF_CTX_ENTRY)
				{
					ClassDefPtr pClassDefEntry;
					pEntry->getClass(pClassDefEntry);

					varsDecls = pClassDefEntry->getVariableDecls();
				}
				else if (pEntry->getStaticEntryType() == INTERFACE_DEF_CTX_ENTRY)
				{
					InterfaceDefPtr pInterfaceDefEntry;
					pEntry->getInterface(pInterfaceDefEntry);

					varsDecls = pInterfaceDefEntry->getVariableDecls();
				}
				else
				{
					return false;
				}

				bool isObject = (refType.getBasicType() == OBJECT_REF_TYPE);

				list<VariableDeclDefPtr>::const_iterator it;

				for (it = varsDecls.begin(); it != varsDecls.end(); it++)
				{
					VariableDeclDefPtr varDecl = *it;
					if (varDecl->getName() == pathElement)
					{
						if (isObject && varDecl->isStatic())
						{
							return false;
						}
						else if (!isObject && !varDecl->isStatic())
						{
							return false;
						}

						pNextType = varDecl->getDeclaredType();
						return true;
					}
				}
			}
			break;
		default:
			assert(false);
		}

		return false;
	}

}