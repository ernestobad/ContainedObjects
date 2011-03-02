
#pragma once

#include "runtime_types.h"

namespace COBJ
{
	using namespace std;

	class IObject
	{
	public:
        virtual ~IObject(){}

		virtual bool isNative() const = 0;

		virtual const IClass& getClass() const = 0;

		virtual bool implements(const wstring& interfaceName) const = 0;

		virtual const IInterfacePtr& getInterface(const wstring& interfaceName) const = 0;

		virtual bool hasMemberVariable(const wstring& varName) const = 0;

		virtual const IVariablePtr& getMemberVariable(const wstring& varName) const = 0;
	};
}
