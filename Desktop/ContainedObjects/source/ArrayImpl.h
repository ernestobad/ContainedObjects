#pragma once

#include "IArray.h"
#include "runtime_types.h"

namespace COBJ
{
	using namespace std;

	class ArrayImpl : public IArray
	{
	public:
		ArrayImpl(basic_type basicType, int length);
		~ArrayImpl(void);

		basic_type getBasicType() const;

		int getLength() const;

		void assignAt(int idx, IVariable& var);

		int getIntegerAt(int idx) const;

		void setIntegerAt(int idx, int value);

		float getFloatAt(int idx) const;

		void setFloatAt(int idx, float value);

		wstring& getStringAt(int idx) const;

		void setStringAt(int idx, const wstring& value);

		IArrayPtr getArrayAt(int idx) const;

		void setArrayAt(int idx, const IArrayPtr& pValue);

		IObjectPtr getObjectAt(int idx) const;

		void setObjectAt(int idx, const IObjectPtr& pValue);

		IClassPtr getClassAt(int idx) const;

		void setClassAt(int idx, const IClassPtr& pValue);

	private:
		inline void checkBoundsAndType(int idx, basic_type basicType) const;

		const basic_type m_BasicType;
		const int m_Length;
		vector<boost::shared_ptr<void>> m_Values;
	};
}