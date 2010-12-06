
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

		virtual const ClassDefBasePtr& getDefinition() const = 0;

		virtual bool isInterface() const = 0;

		virtual void newObject(
			const map<const wstring, IVariablePtr>& params,
			IObjectPtr& pObject) const = 0;

		virtual bool implements(const wstring& interfaceName) const = 0;

		virtual const IInterfacePtr& getInterface(const wstring& interfaceName) const = 0;

		virtual bool hasStaticVariable(const wstring& varName) const = 0;

		virtual const IVariablePtr& getStaticVariable(const wstring& varName) const = 0;
	};
}
