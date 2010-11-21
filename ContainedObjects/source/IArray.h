#pragma once

#include "runtime_types.h"

namespace COBJ
{
	class IArray
	{
	public:
        virtual ~IArray(){}

		virtual int getLength() const = 0;

		virtual bool getIntegerAt(int idx, int& intValue) const = 0;

		virtual bool setIntegerAt(int idx, int intValue) = 0;

		virtual bool getFloatAt(int idx, float& floatValue) const = 0;

		virtual bool setFloatAt(int idx, float floatValue) = 0;

		virtual bool getStringAt(int idx, wstring& string) const = 0;

		virtual bool setStringAt(int idx, const wstring& string) const = 0;

		virtual bool getObjectAt(int idx, IObjectPtr& pObject) const = 0;

		virtual bool setObjectAt(int idx, const IObjectPtr& pObject) const = 0;
	};
}
