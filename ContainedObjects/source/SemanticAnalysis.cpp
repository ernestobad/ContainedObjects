#include "platform.h"
#include "SemanticAnalysis.h"
#include "Context.h"
#include "StaticContextEntry.h"
#include "ICheck.h"
#include "ClassDef.h"
#include "InterfaceDef.h"
#include "ValueDef.h"
#include "VariableDeclDef.h"
#include "FormalParamDef.h"
#include "ObjectInitValueDef.h"
#include "ArrayInitValueDef.h"
#include "LiteralValueDef.h"
#include "ActualParamDef.h"
#include "ReferencePathValueDef.h"
#include "Type.h"
#include "PrimitiveType.h"
#include "ReferenceType.h"
#include "Log.h"
#include "LogEntry.h"
#include "message_code.h"

namespace COBJ
{
	using namespace std;

	SemanticAnalysis::SemanticAnalysis(const boost::shared_ptr<Log>& pLog)
		: m_pLog(pLog)
	{
	}

	SemanticAnalysis::~SemanticAnalysis(void)
	{
	}

	void SemanticAnalysis::addCheck(const ICheckPtr& pCheck)
	{

	}

	void SemanticAnalysis::analyze(
			const list<ClassDefPtr>& classes,
			const list<InterfaceDefPtr>& interfaces)
	{
		StaticContextPtr pRootCtx(new StaticContext());

		initRootContext(*pRootCtx, classes, interfaces);
	}

	void SemanticAnalysis::initRootContext(
			StaticContext& ctx,
			const std::list<ClassDefPtr>& classes,
			const std::list<InterfaceDefPtr>& interfaces)
	{
		list<ClassDefPtr>::const_iterator cit;

		for (cit = classes.begin(); cit != classes.end(); cit++)
		{
			const ClassDefPtr pClassDef = *cit;
			ConstStaticContextEntryPtr pEntry(new StaticContextEntry(pClassDef));
			if (!ctx.addEntry(pEntry))
			{
				boost::wformat f(L"%1% already exists in context.");
				f % pEntry->getName();
				m_pLog->log(*pClassDef, msg::ErrAnaCtxInit_ClassNameAlreadyExists, f.str());
				continue;
			}
		}

		list<InterfaceDefPtr>::const_iterator iit;

		for (iit = interfaces.begin(); iit != interfaces.end(); iit++)
		{
			const InterfaceDefPtr pInterfaceDef = *iit;
			ConstStaticContextEntryPtr pEntry(new StaticContextEntry(pInterfaceDef));
			if (!ctx.addEntry(pEntry))
			{
				boost::wformat f(L"%1% already exists in context.");
				f % pEntry->getName();
				m_pLog->log(*pInterfaceDef, msg::ErrAnaCtxInit_IfaceNameAlreadyExists, f.str());
				continue;
			}
		}
	}

	void SemanticAnalysis::initClassContext(
		StaticContext& ctx,
		const ClassDef& classDef)
	{
		const map<const wstring, FormalParamDefPtr>& formalParamsMap = classDef.getFormalParametersMap();

		map<const wstring, FormalParamDefPtr>::const_iterator fpit;

		for (fpit = formalParamsMap.begin(); fpit != formalParamsMap.end(); fpit++)
		{
			const FormalParamDefPtr& pFormalParamDef = (*fpit).second;
			StaticContextEntryPtr pEntry(new StaticContextEntry(pFormalParamDef));
			if (!ctx.addEntry(pEntry))
			{
				boost::wformat f(L"%1% already exists in context.");
				f % pEntry->getName();
				m_pLog->log(*pFormalParamDef, msg::ErrAnaCtxInit_FParmNameAlreadyExsits, f.str());
				continue;
			}
		}

		const list<VariableDeclDefPtr>& variables = classDef.getVariableDecls();

		list<VariableDeclDefPtr>::const_iterator vit;

		for (vit = variables.begin(); vit != variables.end(); vit++)
		{
			const VariableDeclDefPtr& pVariableDef = *vit;
			StaticContextEntryPtr pEntry(new StaticContextEntry(pVariableDef));
			if (!ctx.addEntry(pEntry))
			{
				boost::wformat f(L"%1% already exists in context.");
				f % pEntry->getName();
				m_pLog->log(*pVariableDef, msg::ErrAnaCtxInit_VarNameAlreadyExsits, f.str());
				continue;
			}
		}
	}

	void SemanticAnalysis::inferTypes(
			list<ClassDefPtr>& classes,
			ConstStaticContextPtr& rootCtx)
	{
		list<ClassDefPtr>::iterator cit;

		for (cit = classes.begin(); cit != classes.end(); cit++)
		{
			ClassDefPtr& pClassDef = *cit;

			StaticContextPtr pClassCtx(new StaticContext(rootCtx));

			initClassContext(*pClassCtx, *pClassDef);

			const list<VariableDeclDefPtr>& variables = pClassDef->getVariableDecls();

			list<VariableDeclDefPtr>::const_iterator vit;

			for (vit = variables.begin(); vit != variables.end(); vit++)
			{
				const VariableDeclDefPtr& pVariable = *vit;
				const ValueDefPtr& pValueDef = pVariable->getValue();

				inferTypes(*pValueDef, rootCtx);
			}
		}
	}

	void SemanticAnalysis::inferTypes(
		ValueDef& valueDef,
		ConstStaticContextPtr& pClassCtx)
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

					inferTypes(*pParamValueDef, pClassCtx);
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

					inferTypes(*pArrayValue, pClassCtx);
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

				const list<wstring>& path = referencePathDef.getReferencePath();

				StaticContextEntryPtr pEntry;

				ConstTypePtr pCurrentType;

				list<wstring>::const_iterator it;

				wstring parentPath(L"");

				for (it = path.begin(); it != path.end(); it++)
				{
					const wstring& pathElement = *it;

					if (it == path.begin())
					{
						ConstStaticContextEntryPtr pEntry;

						if (!pClassCtx->lookup(pathElement, pEntry))
						{
							boost::wformat f(L"Unable to resolve name %1%");
							f % pathElement;
							m_pLog->log(referencePathDef, msg::ErrAnaTypeInfer_NameNotInContext, f.str());
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
									pCurrentType = pVariableDef->getDeclaredType();
								}
								break;
							case FORMAL_PARAM_DEF_CTX_ENTRY:
								{
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

						ConstStaticContextPtr pRootCtx = pClassCtx;
						pClassCtx->getRootContext(pRootCtx);

						if (!followPathElement(
								*pCurrentType,
								*pRootCtx,
								pathElement,
								pCurrentType))
						{
							boost::wformat f(L"%1% is not a member of %2%");
							f % pathElement % parentPath;
							m_pLog->log(referencePathDef, msg::ErrAnaTypeInfer_NotAMember, f.str());
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

	bool SemanticAnalysis::followPathElement(
			const Type& currentType,
			const StaticContext& rootCtx,
			const wstring& pathElement,
			ConstTypePtr& pNextType)
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

				ConstStaticContextEntryPtr pEntry;

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