
#pragma once

class IIClass;
class IIVariable;

namespace COBJ
{
	class IObject
	{
	public:
        virtual ~IObject(){}

		virtual bool isNative() const = 0;

		virtual Result getClass(IIClass** ppClass) const = 0;

		virtual Result getMemberVariable(
			const std::wstring& varName, IVariable** ppVar) const = 0;
	};
}
