#pragma once

#include "runtime_types.h"
#include "ast_types.h"
#include "IVariable.h"

namespace COBJ
{
	using namespace std;

	class VariableImpl : public IVariable
	{
	public:
		VariableImpl(basic_type basicType);
		~VariableImpl(void);

		basic_type getBasicType();

		void assign(IVariable& var);

		int getInteger() const;

		void setInteger(int value);

		float getFloat() const;

		void setFloat(float value);

		wstring& getString() const;

		void setString(const wstring& value);

		IArrayPtr getArray() const;

		void setArray(const IArrayPtr& pValue);

		IObjectPtr getObject() const;

		void setObject(const IObjectPtr& pValue);

		IClassPtr getClass() const;

		void setClass(const IClassPtr& pValue);

	private:
		inline void VariableImpl::checkBasicType(basic_type basicType) const;

		const basic_type m_BasicType;
		boost::shared_ptr<void> m_pValue;
	};
}