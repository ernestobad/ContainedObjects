
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

		virtual void getClass(IClassPtr& pClass) const = 0;

		virtual bool getMemberVariable(
			const wstring& varName,
			IVariablePtr& pVar) const = 0;
	};
}
