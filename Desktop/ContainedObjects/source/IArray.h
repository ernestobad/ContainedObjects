#pragma once

#include "runtime_types.h"
#include "ast_types.h"

namespace COBJ
{
	using namespace std;

	class IArray
	{
	public:
        virtual ~IArray(){}

		virtual basic_type getBasicType() const = 0;

		virtual void assignAt(int idx, IVariable& var) = 0;

		virtual int getLength() const = 0;

		virtual int getIntegerAt(int idx) const = 0;

		virtual void setIntegerAt(int idx, int value) = 0;

		virtual float getFloatAt(int idx) const = 0;

		virtual void setFloatAt(int idx, float value) = 0;

		virtual wstring& getStringAt(int idx) const = 0;

		virtual void setStringAt(int idx, const wstring& value) = 0;

		virtual IArrayPtr getArrayAt(int idx) const = 0;

		virtual void setArrayAt(int idx, const IArrayPtr& pValue) = 0;

		virtual IObjectPtr getObjectAt(int idx) const = 0;

		virtual void setObjectAt(int idx, const IObjectPtr& pValue) = 0;

		virtual IClassPtr getClassAt(int idx) const = 0;

		virtual void setClassAt(int idx, const IClassPtr& pValue) = 0;
	};
}
