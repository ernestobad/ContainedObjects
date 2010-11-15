
#pragma once

namespace COBJ
{
	class InterfaceDef;

	class IInterface
	{
	public:
        virtual ~IInterface(){}

		virtual bool isNative() const = 0;

		virtual const InterfaceDef& getDefinition() = 0;
	};
}
