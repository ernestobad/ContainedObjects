
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

		virtual const ClassDefPtr& getDefinition() = 0;

		virtual bool implements(
			const IInterfacePtr pInterface) const = 0;

		virtual Result getImplementedInterfaces(
			vector<const IInterfacePtr>& interfaces) const = 0;

		virtual Result newObject(
			const map<const wstring, const IVariablePtr>& params,
			IObjectPtr ppObject) = 0;

		virtual Result getStaticVariable(
			const std::wstring& varName, IVariable** ppVariable) const = 0;
	};
}
