
#pragma once

#include "ast_types.h"
#include "runtime_types.h"

namespace COBJ
{
	using namespace std;

	class IClass
	{
	public:
        virtual ~IClass(){}

		virtual bool isNative() const = 0;

		virtual const ClassDefPtr& getDefinition() const = 0;

		virtual bool implements(
			const wstring interfaceName) const = 0;

		virtual void getImplementedInterfaces(
			list<const IInterfacePtr>& interfaces) const = 0;

		virtual void newObject(
			const map<const wstring, IVariablePtr>& params,
			IObjectPtr pObject) const = 0;

		virtual bool getStaticVariable(
			const wstring& varName,
			IVariablePtr& pVariable) const = 0;
	};
}
