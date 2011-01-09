#include "platform.h"
#include "ClassImpl.h"
#include "ClassDefBase.h"
#include "exceptions.h"
#include "Context.h"
#include "RuntimeContextEntry.h"
#include "RuntimeContextHelper.h"
#include "VariableDeclDef.h"
#include "eval.h"
#include "InterfaceImpl.h"
#include "ObjectImpl.h"

namespace COBJ
{
	ClassImpl::ClassImpl(const ClassDefBasePtr& pClassDefBase, const RuntimeContextPtr& pRootCtx)
		: m_pClassDefBase(pClassDefBase), m_pClassCtx()
	{
		RuntimeContextHelper::newClassContext(m_pClassCtx, pRootCtx);

		if (!isInterface())
		{
			const list<VariableDeclDefPtr>& varDefs = pClassDefBase->getVariableDecls();

			list<VariableDeclDefPtr>::const_iterator vit;

			for (vit = varDefs.begin(); vit != varDefs.end(); vit++)
			{
				const VariableDeclDefPtr& pVarDef = *vit;

				if (!pVarDef->isStatic())
					continue;

				const wstring& varName = pVarDef->getName();

				IVariablePtr pStaticVar;
				eval(pVarDef->getValue(), m_pClassCtx, pStaticVar);

				m_VarsMap[varName] = pStaticVar;

				RuntimeContextEntryPtr pEntry(new RuntimeContextEntry(varName, pStaticVar));
				m_pClassCtx->addEntry(pEntry);
			}

			RuntimeContextPtr pRootCtx;
			m_pClassCtx->getRootContext(pRootCtx);

			const list<const wstring>& interfaceNames = pClassDefBase->getImplementedInterfaces();

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
	}

	ClassImpl::~ClassImpl(void)
	{
	}

	bool ClassImpl::isNative() const
	{
		return false;
	}

	const ClassDefBasePtr& ClassImpl::getDefinition() const
	{
		return m_pClassDefBase;
	}

	bool ClassImpl::isInterface() const
	{
		return (m_pClassDefBase->getASTNodeType() == ASTN_INTERFACE);
	}

	void ClassImpl::newObject(
		const map<const wstring, IVariablePtr>& params,
		IObjectPtr& pObject) const
	{
		pObject = IObjectPtr(new ObjectImpl(*this, params, m_pClassCtx));
	}

	bool ClassImpl::hasStaticVariable(const wstring& varName) const
	{
		return (m_VarsMap.find(varName) != m_VarsMap.end());
	}

	const IVariablePtr& ClassImpl::getStaticVariable(const wstring& varName) const
	{
		map<const wstring, IVariablePtr>::const_iterator it;

		it = m_VarsMap.find(varName);

		if (it == m_VarsMap.end())
		{
			throw RuntimeCheckException(L"Undefined static variable");
		}

		return it->second;
	}

	bool ClassImpl::implements(const wstring& interfaceName) const
	{
		return (m_InterfacesMap.find(interfaceName) != m_InterfacesMap.end());
	}

	const IInterfacePtr& ClassImpl::getInterface(const wstring& interfaceName) const
	{
		map<const wstring, IInterfacePtr>::const_iterator it;

		it = m_InterfacesMap.find(interfaceName);

		if (it == m_InterfacesMap.end())
		{
			throw RuntimeCheckException(L"Interface not implemented");
		}

		return it->second;
	}
}