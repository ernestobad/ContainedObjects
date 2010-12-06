#pragma once

#include "IClass.h"
#include "ast_types.h"
#include "runtime_types.h"

namespace COBJ
{
	class ClassImpl : public IClass
	{
	public:
		ClassImpl(const ClassDefBasePtr pClassDefBase, const RuntimeContextPtr& pRootCtx);
		~ClassImpl(void);

		bool isNative() const;

		bool isInterface() const;

		const ClassDefBasePtr& getDefinition() const;

		void newObject(
			const map<const wstring, IVariablePtr>& params,
			IObjectPtr& pObject) const;

		bool implements(const wstring& interfaceName) const;

		const IVariablePtr& getStaticVariable(const wstring& varName) const;

		bool hasStaticVariable(const wstring& varName) const;

		const IInterfacePtr& getInterface(const wstring& interfaceName) const;

	private:
		RuntimeContextPtr m_pClassCtx;
		ClassDefBasePtr m_pClassDefBase;
		map<const wstring, IVariablePtr> m_VarsMap;
		map<const wstring, IInterfacePtr> m_InterfacesMap;
	};
}