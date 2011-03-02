#include "platform.h"
#include "VariableImpl.h"
#include "IArray.h"
#include "IObject.h"
#include "IClass.h"
#include "Type.h"
#include "exceptions.h"

namespace COBJ
{
	using namespace std;

	VariableImpl::VariableImpl(basic_type basicType)
		: m_BasicType(basicType)
	{
		switch (basicType)
		{
		case INTEGER_B_TYPE:
			{
				m_pValue = boost::shared_ptr<int>(new int(0));
				break;
			}
		case FLOAT_B_TYPE:
			{
				m_pValue = boost::shared_ptr<float>(new float(0.0));
				break;
			}
		case STRING_B_TYPE:
			{
				m_pValue = boost::shared_ptr<wstring>(new wstring(L""));
				break;
			}
		case ARRAY_B_TYPE:
			{
				m_pValue = boost::shared_ptr<IArrayPtr>();
				break;
			}
		case OBJECT_B_TYPE:
			{
				m_pValue = boost::shared_ptr<IObjectPtr>();
				break;
			}
		case CLASS_B_TYPE:
			{
				m_pValue = boost::shared_ptr<IClassPtr>();
				break;
			}
		default:
			{
				throw InternalErrorException(L"Unexpected basic type");
			}
		}
	}

	VariableImpl::~VariableImpl(void)
	{
	}

	basic_type VariableImpl::getBasicType() const
	{
		return m_BasicType;
	}

	void VariableImpl::assign(const IVariable& var)
	{
		switch (var.getBasicType())
		{
		case INTEGER_B_TYPE:
			{
				setInteger(var.getInteger());
				break;
			}
		case FLOAT_B_TYPE:
			{
				setFloat(var.getFloat());
				break;
			}
		case STRING_B_TYPE:
			{
				setString(var.getString());
				break;
			}
		case ARRAY_B_TYPE:
			{
				setArray(var.getArray());
				break;
			}
		case OBJECT_B_TYPE:
			{
				setObject(var.getObject());
				break;
			}
		case CLASS_B_TYPE:
			{
				setClass(var.getClass());
				break;
			}
		default:
			{
				throw InternalErrorException(L"Unexpected basic type");
			}
		}
	}

	inline void VariableImpl::checkBasicType(basic_type basicType) const
	{
		if (m_BasicType != basicType)
		{
			throw InvalidTypeException(L"Invalid type");
		}
	}

	int VariableImpl::getInteger() const
	{
		checkBasicType(INTEGER_B_TYPE);
		
		return *((int*) m_pValue.get());
	}

	void VariableImpl::setInteger(int value)
	{
		checkBasicType(INTEGER_B_TYPE);

		*((int*) m_pValue.get()) = value;
	}

	float VariableImpl::getFloat() const
	{
		checkBasicType(FLOAT_B_TYPE);

		return *((float*) m_pValue.get());
	}

	void VariableImpl::setFloat(float value)
	{
		checkBasicType(FLOAT_B_TYPE);

		*((float*) m_pValue.get()) = value;
	}

	wstring& VariableImpl::getString() const
	{
		checkBasicType(STRING_B_TYPE);

		return *((wstring*) m_pValue.get());
	}

	void VariableImpl::setString(const wstring& value)
	{
		checkBasicType(STRING_B_TYPE);

		*((wstring*) m_pValue.get()) = value;
	}

	IArrayPtr VariableImpl::getArray() const
	{
		checkBasicType(ARRAY_B_TYPE);

		return boost::static_pointer_cast<IArray>(m_pValue);
	}

	void VariableImpl::setArray(const IArrayPtr& pValue)
	{
		checkBasicType(ARRAY_B_TYPE);

		m_pValue = pValue;
	}

	IObjectPtr VariableImpl::getObject() const
	{
		checkBasicType(OBJECT_B_TYPE);

		return boost::static_pointer_cast<IObject>(m_pValue);
	}

	void VariableImpl::setObject(const IObjectPtr& pValue)
	{
		checkBasicType(OBJECT_B_TYPE);

		m_pValue = pValue;
	}

	IClassPtr VariableImpl::getClass() const
	{
		checkBasicType(CLASS_B_TYPE);

		return boost::static_pointer_cast<IClass>(m_pValue);
	}

	void VariableImpl::setClass(const IClassPtr& pValue)
	{
		checkBasicType(CLASS_B_TYPE);

		m_pValue = pValue;
	}
}