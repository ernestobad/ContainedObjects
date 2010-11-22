#include "platform.h"
#include "ClassImpl.h"

namespace COBJ
{
	ClassImpl::ClassImpl(const ClassDefPtr pClassDef, const RuntimeContextPtr& pRootCtx)
	{
	}

	ClassImpl::~ClassImpl(void)
	{
	}

	bool ClassImpl::isNative() const
	{
		// TODO:
		return false;
	}

	const ClassDefPtr& ClassImpl::getDefinition() const
	{
		return m_pClassDef;
	}

	bool ClassImpl::implements(
		const wstring interfaceName) const
	{
		// TODO:
		return false;
	}

	void ClassImpl::getImplementedInterfaces(
		list<const IInterfacePtr>& interfaces) const
	{
		// TODO:
	}

	void ClassImpl::newObject(
		const map<const wstring, const IVariablePtr>& params,
		IObjectPtr ppObject) const
	{
		// TODO:
	}

	bool ClassImpl::getStaticVariable(
		const wstring& varName,
		IVariablePtr& pVariable) const
	{
		// TODO:
		return false;
	}
}