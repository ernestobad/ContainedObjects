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
#include "StaticContextHelper.h"
#include "TypeInference.h"

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

		StaticContextPtr pRootCtx;
		StaticContextHelper::newRootContext(pRootCtx, classes, m_pLog);
		TypeInference::inferTypes(classes, pRootCtx, m_pLog);

		list<ClassDefBasePtr>::const_iterator it;
		for (it = classes.begin(); it != classes.end(); it++)
		{
			const ClassDefBasePtr& pClassDefBase = *it;

			checkClassContext(pClassDefBase, pRootCtx);
			checkInstanceContext(pClassDefBase, pRootCtx);
		}
	}

	void SemanticAnalysis::checkClassContext(
		const ClassDefBasePtr& pClassDefBase,
		const StaticContextPtr& pCtx)
	{
		StaticContextPtr pClassCtx;

		StaticContextHelper::newClassContext(
			pClassCtx,
			pClassDefBase,
			pCtx,
			m_pLog);

		const list<VariableDeclDefPtr>& varDecls = pClassDefBase->getVariableDecls();
		list<VariableDeclDefPtr>::const_iterator vit;

		for (vit = varDecls.begin(); vit != varDecls.end(); vit++)
		{
			const VariableDeclDefPtr& pVarDecl = *vit;
			if (pVarDecl->isStatic())
			{
				check(pVarDecl, pClassCtx);
				StaticContextEntryPtr pEntry(new StaticContextEntry(pVarDecl));
				pClassCtx->addEntry(pEntry);

				findStaticDependencies(pClassDefBase, pClassCtx, pVarDecl->getValue());
			}
		}
	}

	void SemanticAnalysis::findStaticDependencies(
			const ClassDefBasePtr& pClassDefBase,
			const StaticContextPtr& pClassCtx,
			const ASTNodePtr& pNode)
	{
		if (pNode.get() == NULL)
			return;

		if (pNode->getASTNodeType() == ASTN_REFERENCE_PATH_VALUE)
		{
			ReferencePathValueDefPtr pRefPathDef = boost::static_pointer_cast<ReferencePathValueDef>(pNode);

			const list<const wstring>& path = pRefPathDef->getReferencePath();

			if (path.size() != 0)
			{
				const wstring& name = *(path.begin());

				CStaticContextEntryPtr pEntry;
				if (pClassCtx->lookup(name, pEntry))
				{
					if ((pEntry->getStaticEntryType() == CLASS_DEF_CTX_ENTRY) || 
						(pEntry->getStaticEntryType() == INTERFACE_DEF_CTX_ENTRY))
					{
						pClassDefBase->addStaticDependency(name);
					}
				}
			}
		}

		list<ASTNodePtr> children;
		pNode->getChildNodes(children);

		list<ASTNodePtr>::iterator it;

		for (it = children.begin(); it != children.end(); it++)
		{
			findStaticDependencies(pClassDefBase, pClassCtx, *it);
		}
	}

	void SemanticAnalysis::checkInstanceContext(
		const ClassDefBasePtr& pClassDefBase,
		const StaticContextPtr& pCtx)
	{
		StaticContextPtr pNewCtx;

		StaticContextHelper::newInstanceContext(
			pNewCtx,
			pClassDefBase,
			pCtx,
			m_pLog);

		const map<const wstring, FormalParamDefPtr> formalParamsMap
			= pClassDefBase->getFormalParametersMap();
		map<const wstring, FormalParamDefPtr>::const_iterator fit;

		for (fit = formalParamsMap.begin(); fit != formalParamsMap.end(); fit++)
		{
			const FormalParamDefPtr& pFormalParam = fit->second;
			check(pFormalParam, pNewCtx);

			StaticContextEntryPtr pEntry(new StaticContextEntry(pFormalParam));
			pNewCtx->addEntry(pEntry);
		}

		const list<VariableDeclDefPtr>& varDecls = pClassDefBase->getVariableDecls();
		list<VariableDeclDefPtr>::const_iterator vit;

		for (vit = varDecls.begin(); vit != varDecls.end(); vit++)
		{
			const VariableDeclDefPtr& pVarDecl = *vit;

			if (!pVarDecl->isStatic())
			{
				check(pVarDecl, pNewCtx);
			}

			StaticContextEntryPtr pEntry(new StaticContextEntry(pVarDecl));
			pNewCtx->addEntry(pEntry);
		}
	}

	void SemanticAnalysis::check(
		const ASTNodePtr& pNode,
		const StaticContextPtr& pCtx)
	{
		list<ICheckPtr>::const_iterator it;

		for (it = m_SemanticChecks.begin(); it != m_SemanticChecks.end(); it++)
		{
			const ICheckPtr& pCheck = *it;
			pCheck->doCheck(pCtx, pNode, m_pLog);
		}

		list<ASTNodePtr> children;
		pNode->getChildNodes(children);

		list<ASTNodePtr>::const_iterator cit;

		for (cit = children.begin(); cit != children.end(); cit++)
		{
			const ASTNodePtr& pChild = *cit;
			check(pChild, pCtx);
		}
	}

	bool SemanticAnalysis::isTypeAssignableFrom(
			const TypePtr& pLType,
			const TypePtr& pRType,
			const StaticContextPtr& pRootCtx)
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

			CStaticContextEntryPtr pRCtxEntry;

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