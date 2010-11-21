#include "platform.h"
#include "ClassCheck.h"
#include "Context.h"
#include "StaticContextEntry.h"
#include "ASTNode.h"
#include "Log.h"
#include "ClassDef.h"
#include "FormalParamDef.h"
#include "InterfaceDef.h"
#include "SemanticAnalysis.h"
#include "VariableDeclDef.h"

namespace COBJ
{
	using namespace std;

	ClassCheck::ClassCheck(void)
	{
	}

	ClassCheck::~ClassCheck(void)
	{
	}

	void ClassCheck::doCheck(
			const ConstStaticContextPtr& pCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const
	{
		if (pNode->getASTNodeType() != ASTN_CLASS)
		{
			return;
		}

		ConstStaticContextPtr pRootCtx;
		pCtx->getRootContext(pRootCtx);

		ClassDefPtr pClassDef = boost::static_pointer_cast<ClassDef>(pNode);

		const list<const wstring>& ifaces = pClassDef->getImplementedInterfaces();
		
		list<const wstring>::const_iterator it;

		for (it = ifaces.begin(); it != ifaces.end(); it++)
		{
			const wstring& ifaceName = *it;

			ConstStaticContextEntryPtr pEntry;
			InterfaceDefPtr pInterfaceDef;

			if (!pRootCtx->lookup(ifaceName, pEntry))
			{
				boost::wformat f(L"Interface %1% not found.");
				f % ifaceName;
				pLog->log(*pClassDef, msg::ErrAnaClassDef_IfaceNotFound, f.str());
				continue;
			}
			else if (pEntry->getInterface(pInterfaceDef))
			{
				boost::wformat f(L"%1% is not an interface.");
				f % ifaceName;
				pLog->log(*pClassDef, msg::ErrAnaClassDef_NotAnIface, f.str());
				continue;
			}

			checkInterfaceParams(pClassDef, pInterfaceDef, pCtx, pLog);
			checkInterfaceVars(pClassDef, pInterfaceDef, pCtx, pLog);
		}

		const list<VariableDeclDefPtr>& vars = pClassDef->getVariableDecls();

		list<VariableDeclDefPtr>::const_iterator vit;

		for (vit = vars.begin(); vit != vars.end(); vit++)
		{
			const VariableDeclDefPtr& pVar = *vit;

			if (pVar->getValue().get() == NULL)
			{
				boost::wformat f(L"Unassigned class variable %1%.");
				f % pVar->getName();
				pLog->log(*pClassDef, msg::ErrAnaClassDef_UnassignedClassVar, f.str());
				continue;
			}
		}
	}

	void ClassCheck::checkInterfaceParams(
		const ClassDefPtr& pClassDef,
		const InterfaceDefPtr& pInterfaceDef,
		const ConstStaticContextPtr& pCtx,
		const LogPtr& pLog) const
	{
		ConstStaticContextPtr pRootCtx;
		pCtx->getRootContext(pRootCtx);

		const map<const wstring, FormalParamDefPtr>& ifaceFormalParams =
			pInterfaceDef->getFormalParametersMap();

		const map<const wstring, FormalParamDefPtr>& classFormalParams =
			pClassDef->getFormalParametersMap();

		if (ifaceFormalParams.empty())
		{
			return;
		}

		map<const wstring, FormalParamDefPtr>::const_iterator iit;
		map<const wstring, FormalParamDefPtr>::const_iterator cit;

		for (iit = ifaceFormalParams.begin(); iit != ifaceFormalParams.end(); iit++)
		{
			const FormalParamDefPtr& pIfaceParam = (*iit).second;
			cit = classFormalParams.find(pIfaceParam->getParamName());
			if (cit == classFormalParams.end())
			{
				boost::wformat f(L"Interface parameter %1% not found.");
				f % pIfaceParam->getParamName();
				pLog->log(*pClassDef, msg::ErrAnaClassDef_MissingIfaceParam, f.str());
				continue;
			}

			const FormalParamDefPtr& pClassParam = (*cit).second;

			if (!isTypeAssignableFrom(
					pClassParam->getType(),
					pIfaceParam->getType(),
					pRootCtx))
			{
				boost::wformat f(
					L"Can't convert from %1% to %2% at class parameter %3% defined on interface %4%.");
				f % pIfaceParam->getType()->toString() % 
					pClassParam->getType()->toString() % 
					pIfaceParam->getParamName() %
					pInterfaceDef->getClassName();
				pLog->log(*pClassDef, msg::ErrAnaClassDef_IfaceParamIncompTypes, f.str());
				continue;
			}
		}

		for (cit = classFormalParams.begin(); cit != classFormalParams.end(); cit++)
		{
			const wstring& classParamName = (*cit).first;

			iit = ifaceFormalParams.find(classParamName);
			if (cit == ifaceFormalParams.end())
			{
				boost::wformat f(L"Class parameter %1% not defined on interface %2%.");
				f % classParamName % pInterfaceDef->getClassName();
				pLog->log(*pClassDef, msg::ErrAnaClassDef_ClassParamNotFoundIface, f.str());
				continue;
			}
		}
	}

	void ClassCheck::checkInterfaceVars(
		const ClassDefPtr& pClassDef,
		const InterfaceDefPtr& pInterfaceDef,
		const ConstStaticContextPtr& pCtx,
		const LogPtr& pLog) const
	{
		ConstStaticContextPtr pRootCtx;
		pCtx->getRootContext(pRootCtx);

		const list<VariableDeclDefPtr>& classVars = pClassDef->getVariableDecls();
		const list<VariableDeclDefPtr>& ifaceVars = pInterfaceDef->getVariableDecls();

		map<const wstring, VariableDeclDefPtr> classVarsMap;
		map<const wstring, VariableDeclDefPtr>::const_iterator mit;

		list<VariableDeclDefPtr>::const_iterator cit;

		for (cit = classVars.begin(); cit != classVars.end(); cit++)
		{
			const VariableDeclDefPtr& pVariableDecl = *cit;
			classVarsMap[pVariableDecl->getName()] = pVariableDecl;
		}

		list<VariableDeclDefPtr>::const_iterator iit;

		for (iit = ifaceVars.begin(); iit != ifaceVars.end(); iit++)
		{
			const VariableDeclDefPtr& pIfaceVariableDecl = *iit;
			const wstring& variableName = pIfaceVariableDecl->getName();

			if ((mit = classVarsMap.find(variableName)) == classVarsMap.end())
			{
				boost::wformat f(L"Variable %1% defined on interface %2% not found in class.");
				f % variableName % pInterfaceDef->getClassName();
				pLog->log(*pClassDef, msg::ErrAnaClassDef_MissingIfaceVar, f.str());
				continue;
			}

			const VariableDeclDefPtr& pClassVariableDecl = (*mit).second;

			if (pIfaceVariableDecl->isStatic() != pClassVariableDecl->isStatic())
			{
				boost::wformat f(L"Variable %1% has invalid scope. See interface %2%");
				f % variableName % pInterfaceDef->getClassName();
				pLog->log(*pClassVariableDecl, msg::ErrAnaClassDef_IfaceVarWrongScope, f.str());
				continue;
			}

			if (!isTypeAssignableFrom(
					pClassVariableDecl->getDeclaredType(),
					pIfaceVariableDecl->getDeclaredType(),
					pRootCtx))
			{
				boost::wformat f(L"Can't convert from %1% to %2% at class variable %3% defined on interface %4%");
				f % pIfaceVariableDecl->getDeclaredType()->toString()%
					pClassVariableDecl->getDeclaredType()->toString() %
					variableName %
					pInterfaceDef->getClassName();
				pLog->log(*pClassVariableDecl, msg::ErrAnaClassDef_IfaceVarIncompTypes, f.str());
				continue;
			}
		}
	}

}