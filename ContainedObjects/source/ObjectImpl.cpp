#include "platform.h"
#include "ObjectImpl.h"
#include "ClassImpl.h"
#include "VariableImpl.h"
#include "eval.h"
#include "Context.h"
#include "RuntimeContextEntry.h"
#include "ClassDef.h"
#include "RuntimeContextHelper.h"
#include "VariableDeclDef.h"
#include "exceptions.h"
#include "InterfaceImpl.h"

namespace COBJ
{
	using namespace std;

	ObjectImpl::ObjectImpl(
		const IClass& iClass,
		const map<const wstring, IVariablePtr>& params,
		const RuntimeContextPtr& pClassContext)
		: m_IClass(iClass)
	{
		RuntimeContextPtr pInstanceCtx;

		RuntimeContextHelper::newInstanceContext(pInstanceCtx, params, pClassContext);

		const ClassDefBasePtr& pClassDef = m_IClass.getDefinition();

		map<const wstring, FormalParamDefPtr> formalParams = pClassDef->getFormalParametersMap();

		map<const wstring, IVariablePtr>::const_iterator apit;

		for (apit = params.begin(); apit != params.end(); apit++)
		{
			const wstring& actualParamName = apit->first;
			if (formalParams.find(actualParamName) == formalParams.end())
			{
				throw RuntimeCheckException(L"Unknown parameter");
			}
		}

		map<const wstring, FormalParamDefPtr>::const_iterator fpit;

		for (fpit = formalParams.begin(); fpit != formalParams.end(); fpit++)
		{
			const wstring& formalParamName = fpit->first;
			if (params.find(formalParamName) == params.end())
			{
				throw RuntimeCheckException(L"Missing parameter");
			}

			// Type Checking? nah
		}

		const list<VariableDeclDefPtr>& varDefs = pClassDef->getVariableDecls();

		list<VariableDeclDefPtr>::const_iterator vit;

		for (vit = varDefs.begin(); vit != varDefs.end(); vit++)
		{
			const VariableDeclDefPtr& pVarDef = *vit;

			if (pVarDef->isStatic())
				continue;

			const wstring& varName = pVarDef->getName();

			IVariablePtr pMemberVar;
			eval(pVarDef->getValue(), pInstanceCtx, pMemberVar);

			m_VarsMap[varName] = pMemberVar;

			RuntimeContextEntryPtr pEntry(new RuntimeContextEntry(varName, pMemberVar));
			pInstanceCtx->addEntry(pEntry);
		}

		RuntimeContextPtr pRootCtx;
		pInstanceCtx->getRootContext(pRootCtx);

		const list<const wstring>& interfaceNames = pClassDef->getImplementedInterfaces();

		list<const wstring>::const_iterator iit;

		for (iit = interfaceNames.begin(); iit != interfaceNames.end(); iit++)
		{
			const wstring& interfaceName = *iit;

			ConstRuntimeContextEntryPtr pEntry;
			if (!pRootCtx->lookup(interfaceName, pEntry))
			{
				throw RuntimeCheckException(L"Can't find interface in context");
			}

			IClassPtr pClass;
			if (!pEntry->getClass(pClass))
			{
				throw RuntimeCheckException(L"Can't find interface class in context");
			}

			if (!pClass->isInterface())
			{
				throw RuntimeCheckException(L"Not an interface class");
			}

			m_InterfacesMap[interfaceName] = IInterfacePtr(new InterfaceImpl(pClass, this));
		}

	}

	ObjectImpl::~ObjectImpl(void)
	{
	}

	bool ObjectImpl::isNative() const
	{
		return false;
	}

	const IClass& ObjectImpl::getClass() const
	{
		return m_IClass;
	}

	bool ObjectImpl::implements(const wstring& interfaceName) const
	{
		return (
			m_InterfacesMap.find(interfaceName) != m_InterfacesMap.end());
	}

	const IInterfacePtr& ObjectImpl::getInterface(const wstring& interfaceName) const
	{
		map<const wstring, IInterfacePtr>::const_iterator it;

		it = m_InterfacesMap.find(interfaceName);

		if (it == m_InterfacesMap.end())
		{
			throw RuntimeCheckException(L"Interface not implemented");
		}

		return it->second;
	}

	bool ObjectImpl::hasMemberVariable(const wstring& varName) const
	{
		return (m_VarsMap.find(varName) != m_VarsMap.end());
	}

	const IVariablePtr& ObjectImpl::getMemberVariable(const wstring& varName) const
	{
		map<const wstring, IVariablePtr>::const_iterator it;

		it = m_VarsMap.find(varName);

		if (it == m_VarsMap.end())
		{
			throw RuntimeCheckException(L"Undefined variable");
		}

		return it->second;
	}
}