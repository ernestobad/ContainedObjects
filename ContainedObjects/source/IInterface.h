#pragma once

#include "runtime_types.h"

namespace COBJ
{
	class IInterface
	{
	public:
        virtual ~IInterface(){}

		virtual bool isNative() const = 0;

		virtual const IClassPtr& getClass() const = 0;

		virtual const IVariable& getVariable(unsigned int index) const = 0;
	};
}
