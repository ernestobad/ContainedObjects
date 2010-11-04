
#pragma once

class InterfaceDef;

namespace COBJ
{
	class IInterface
	{
	public:
        virtual ~IInterface(){}

		virtual bool isNative() const = 0;

		virtual const InterfaceDef& getDefinition() = 0;
	};
}
