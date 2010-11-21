#include "platform.h"
#include "SemanticAnalysis.h"
#include "Context.h"
#include "StaticContextEntry.h"
#include "ICheck.h"
#include "ClassDefBase.h"
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

	const LogPtr& SemanticAnalysis::getLog() const
	{
		return m_pLog;
	}

	void SemanticAnalysis::addCheck(const ICheckPtr& pCheck)
	{
		m_SemanticChecks.push_back(pCheck);
	}

	void SemanticAnalysis::analyze(
			const list<ClassDefBasePtr>& classes)
	{
		m_pLog->clear();

		ConstStaticContextPtr pRootCtx;
		newRootContext(pRootCtx, classes);
		inferTypes(classes, pRootCtx);

		list<ClassDefBasePtr>::const_iterator it;
		for (it = classes.begin(); it != classes.end(); it++)
		{
			const ClassDefBasePtr& pClassDefBase = *it;
			check(pClassDefBase, pRootCtx);
		}
	}

	void SemanticAnalysis::check(
		const ASTNodePtr& pNode,
		const ConstStaticContextPtr& pCtx)
	{
		list<ICheckPtr>::const_iterator it;

		for (it = m_SemanticChecks.begin(); it != m_SemanticChecks.end(); it++)
		{
			const ICheckPtr& pCheck = *it;
			pCheck->doCheck(pCtx, pNode, m_pLog);
		}

		list<ASTNodePtr> children;
		pNode->getChildNodes(children);

		ConstStaticContextPtr pNewCtx;

		if ((pNode->getASTNodeType() == ASTN_CLASS) || 
			(pNode->getASTNodeType() == ASTN_INTERFACE))
		{
			ClassDefBasePtr pClassDefBase = boost::static_pointer_cast<ClassDefBase>(pNode);

			newClassContext(
				pNewCtx,
				pClassDefBase,
				pCtx);
		}
		else if (pNode->getASTNodeType() == ASTN_VARIABLE_DECL)
		{
			VariableDeclDefPtr pVarDef = boost::static_pointer_cast<VariableDeclDef>(pNode);

			newMemberContext(
				pNewCtx,
				pVarDef,
				pCtx);
		}
		else
		{
			pNewCtx = pCtx;
		}

		list<ASTNodePtr>::const_iterator cit;

		for (cit = children.begin(); cit != children.end(); cit++)
		{
			const ASTNodePtr& pChild = *cit;
			check(pChild, pNewCtx);
		}
	}

	void SemanticAnalysis::newRootContext(
			ConstStaticContextPtr& pNewCtx,
			const std::list<ClassDefBasePtr>& classes)
	{
		StaticContextPtr pCtx(new StaticContext());

		list<ClassDefBasePtr>::const_iterator cit;

		for (cit = classes.begin(); cit != classes.end(); cit++)
		{
			const ClassDefBasePtr pClassDef = *cit;

			ConstStaticContextEntryPtr pEntry(
				pClassDef->getASTNodeType() == ASTN_CLASS ?
				new StaticContextEntry(boost::static_pointer_cast<ClassDef>(pClassDef)) :
				new StaticContextEntry(boost::static_pointer_cast<InterfaceDef>(pClassDef)));

			if (!pCtx->addEntry(pEntry))
			{
				boost::wformat f(L"%1% already exists in context.");
				f % pEntry->getName();
				m_pLog->log(
					*boost::static_pointer_cast<ASTNode>(pClassDef),
					msg::ErrAnaCtxInit_ClassNameAlreadyExists, f.str());
				continue;
			}
		}

		pNewCtx = boost::static_pointer_cast<const StaticContext>(pCtx);
	}

	void SemanticAnalysis::newClassContext(
		ConstStaticContextPtr& pNewCtx,
		const ClassDefBasePtr& pClassDefBase,
		const ConstStaticContextPtr& pRootCtx)
	{
		StaticContextPtr pCtx(new StaticContext(pRootCtx));

		const map<const wstring, FormalParamDefPtr>& formalParamsMap = pClassDefBase->getFormalParametersMap();

		map<const wstring, FormalParamDefPtr>::const_iterator fpit;

		for (fpit = formalParamsMap.begin(); fpit != formalParamsMap.end(); fpit++)
		{
			const FormalParamDefPtr& pFormalParamDef = (*fpit).second;
			StaticContextEntryPtr pEntry(new StaticContextEntry(pFormalParamDef));
			if (!pCtx->addEntry(pEntry))
			{
				boost::wformat f(L"%1% already exists in context.");
				f % pEntry->getName();
				m_pLog->log(*pFormalParamDef, msg::ErrAnaCtxInit_FParmNameAlreadyExsits, f.str());
				continue;
			}
		}

		const list<VariableDeclDefPtr>& variables = pClassDefBase->getVariableDecls();

		list<VariableDeclDefPtr>::const_iterator vit;

		for (vit = variables.begin(); vit != variables.end(); vit++)
		{
			const VariableDeclDefPtr& pVariableDef = *vit;
			StaticContextEntryPtr pEntry(new StaticContextEntry(pVariableDef));
			if (!pCtx->addEntry(pEntry))
			{
				boost::wformat f(L"%1% already exists in context.");
				f % pEntry->getName();
				m_pLog->log(*pVariableDef, msg::ErrAnaCtxInit_VarNameAlreadyExsits, f.str());
				continue;
			}
		}

		pNewCtx = boost::static_pointer_cast<const StaticContext>(pCtx);
	}

	void SemanticAnalysis::newMemberContext(
		ConstStaticContextPtr& pNewCtx,
		const VariableDeclDefPtr& pVarDef,
		const ConstStaticContextPtr& pRootCtx)
	{
		StaticContextPtr pCtx(new StaticContext(pRootCtx, pVarDef->isStatic()));
		pNewCtx = boost::static_pointer_cast<const StaticContext>(pCtx);
	}

	void SemanticAnalysis::inferTypes(
			const list<ClassDefBasePtr>& classes,
			ConstStaticContextPtr& pRootCtx)
	{
		list<ClassDefBasePtr>::const_iterator cit;

		for (cit = classes.begin(); cit != classes.end(); cit++)
		{
			const ClassDefBasePtr& pClassDefBase = *cit;

			if (pClassDefBase->getASTNodeType() == ASTN_INTERFACE)
			{
				continue;
			}

			ConstStaticContextPtr pClassCtx;
			newClassContext(pClassCtx, pClassDefBase, pRootCtx);

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
				
				ConstStaticContextPtr pMemberCtx(new StaticContext(pClassCtx, pVariable->isStatic()));
				inferTypes(*pValueDef, pMemberCtx);
			}
		}
	}

	void SemanticAnalysis::inferTypes(
		ValueDef& valueDef,
		ConstStaticContextPtr& pMemberCtx)
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

					inferTypes(*pParamValueDef, pMemberCtx);
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

					inferTypes(*pArrayValue, pMemberCtx);
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

				TypePtr pCurrentType;

				list<wstring>::const_iterator it;

				wstring parentPath(L"");

				for (it = path.begin(); it != path.end(); it++)
				{
					const wstring& pathElement = *it;

					if (it == path.begin())
					{
						ConstStaticContextEntryPtr pEntry;

						if (!pMemberCtx->lookup(pathElement, pEntry))
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

									if (pMemberCtx->isStatic() && !pVariableDef->isStatic())
									{
										boost::wformat f(L"Cannot refer to a non static variable from an static context: %1%");
										f % pathElement;
										m_pLog->log(referencePathDef, msg::ErrAnaTypeInfer_NonStaticVarRef, f.str());
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
										m_pLog->log(referencePathDef, msg::ErrAnaTypeInfer_NonStaticParamRef, f.str());
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

						ConstStaticContextPtr pRootCtx;
						pMemberCtx->getRootContext(pRootCtx);

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

	bool isTypeAssignableFrom(
			const TypePtr& pLType,
			const TypePtr& pRType,
			const ConstStaticContextPtr& pRootCtx)
	{
		if (*pLType == *pRType)
		{
			return true;
		}
		else if (pLType->getBasicType() != pRType->getBasicType())
		{
			return false;
		}
		else if (pLType->getBasicType() == OBJECT_B_TYPE)
		{
			ReferenceTypePtr pLRefType = 
				boost::static_pointer_cast<ReferenceType>(pLType);

			ReferenceTypePtr pRRefType = 
				boost::static_pointer_cast<ReferenceType>(pRType);

			const wstring& lTypeName = pLRefType->getReferenceTypeName();

			const wstring& rTypeName = pRRefType->getReferenceTypeName();

			ConstStaticContextEntryPtr pRCtxEntry;

			if (!pRootCtx->lookup(rTypeName, pRCtxEntry))
			{
				return false;
			}

			ClassDefPtr pRClass;
			if (!pRCtxEntry->getClass(pRClass))
			{
				// if rh type is an interface, then lh type must be the same interface
				// (ther is no interface inheritance), but we know that *pLType != *pRType
				// so the interfaces are not the same
				return false;
			}

			const list<const wstring>& interfaces = pRClass->getImplementedInterfaces();

			list<const wstring>::const_iterator it;

			for (it = interfaces.begin(); it != interfaces.end(); it++)
			{
				const wstring& ifaceName = *it;
				if (lTypeName == ifaceName)
				{
					return true;
				}
			}

			return false;
		}
		else if (pLType->getBasicType() == ARRAY_B_TYPE)
		{
			ArrayTypePtr pLArrayType = boost::static_pointer_cast<ArrayType>(pLType);
			ArrayTypePtr pRArrayType = boost::static_pointer_cast<ArrayType>(pRType);

			return isTypeAssignableFrom(
				pLArrayType->getChildType(),
				pRArrayType->getChildType(),
				pRootCtx);
		}
		else
		{
			return false;
		}
	}
}