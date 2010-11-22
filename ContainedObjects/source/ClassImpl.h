#pragma once

#include "IClass.h"
#include "ast_types.h"
#include "runtime_types.h"

namespace COBJ
{
	class ClassImpl : public IClass
	{
	public:
		ClassImpl(const ClassDefPtr pClassDef, const RuntimeContextPtr& pRootCtx);
		~ClassImpl(void);

		bool isNative() const;

		const ClassDefPtr& getDefinition() const;

		bool implements(
			const wstring interfaceName) const;

		void getImplementedInterfaces(
			list<const IInterfacePtr>& interfaces) const;

		void newObject(
			const map<const wstring, const IVariablePtr>& params,
			IObjectPtr ppObject) const;

		bool getStaticVariable(
			const wstring& varName, IVariablePtr& pVariable) const;

	private:
		RuntimeContextPtr m_pRootCtx;
		ClassDefPtr m_pClassDef;
	};
}