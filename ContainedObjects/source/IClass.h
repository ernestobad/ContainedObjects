
#pragma once

class IInterface;
class IVariable;
class ClassDef;

namespace COBJ
{
	class IClass
	{
	public:
        virtual ~IClass(){}

		virtual bool isNative() const = 0;

		virtual const ClassDef& getDefinition() = 0;

		virtual bool implements(IInterface* pInterface) const = 0;

		virtual Result getImplementedInterfaces(
			std::vector<IInterface*>& impementedInterfaces) const = 0;

		virtual Result newObject(
			const std::map<std::wstring, boost::shared_ptr<IVariable>>& params,
			IObject** ppObject) = 0;

		virtual Result getStaticVariable(
			const std::wstring& varName, IVariable** ppVariable) const = 0;
	};
}
