#pragma once

#include "runtime_types.h"
#include "ast_types.h"

namespace COBJ
{
	using namespace std;

	class IVariable
	{
	public:
        virtual ~IVariable(){}

		virtual basic_type getBasicType() = 0;

		virtual void assign(IVariable& var) = 0;

		virtual int getInteger() const = 0;

		virtual void setInteger(int value) = 0;

		virtual float getFloat() const = 0;

		virtual void setFloat(float value) = 0;

		virtual wstring& getString() const = 0;

		virtual void setString(const wstring& value) = 0;

		virtual IArrayPtr getArray() const = 0;

		virtual void setArray(const IArrayPtr& pValue) = 0;

		virtual IObjectPtr getObject() const = 0;

		virtual void setObject(const IObjectPtr& pValue) = 0;

		virtual IClassPtr getClass() const = 0;

		virtual void setClass(const IClassPtr& pValue) = 0;
	};
}
