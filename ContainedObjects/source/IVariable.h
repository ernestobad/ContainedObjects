#pragma once

#include "runtime_types.h"
#include "Type.h"

namespace COBJ
{
	using namespace std;

	class IVariable
	{
	public:
        virtual ~IVariable(){}

		virtual basic_type getBasicType() = 0;

		virtual bool getInteger(int& value) const = 0;

		virtual bool setInteger(int value) = 0;

		virtual bool getFloat(float& value) const = 0;

		virtual bool setFloat(float value) = 0;

		virtual bool getString(wstring& value) const = 0;

		virtual bool setString(const wstring& value) const = 0;

		virtual bool getArray(IArrayPtr& pValue) const = 0;

		virtual bool setArray(const IArrayPtr& pValue) const = 0;

		virtual bool getObject(IObjectPtr& pValue) const = 0;

		virtual bool setObject(const IObjectPtr& pValue) const = 0;

		virtual bool getClass(IClassPtr& pValue) const = 0;

		virtual bool setClass(const IClassPtr& pValue) const = 0;
	};
}
