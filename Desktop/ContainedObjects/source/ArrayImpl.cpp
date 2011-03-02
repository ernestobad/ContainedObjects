#include "platform.h"
#include "ArrayImpl.h"
#include "Type.h"
#include "IVariable.h"
#include "IObject.h"
#include "IClass.h"
#include "exceptions.h"

namespace COBJ
{
	using namespace std;

	ArrayImpl::ArrayImpl(basic_type basicType, int length)
		: m_BasicType(basicType), m_Length(length), m_Values(length)
	{
		for (int i = 0; i < length; i++)
		{
			switch (basicType)
			{
			case INTEGER_B_TYPE:
				{
					m_Values[i] = boost::shared_ptr<int>(new int(0));
					break;
				}
			case FLOAT_B_TYPE:
				{
					m_Values[i] = boost::shared_ptr<float>(new float(0.0));
					break;
				}
			case STRING_B_TYPE:
				{
					m_Values[i] = boost::shared_ptr<wstring>(new wstring(L""));
					break;
				}
			case ARRAY_B_TYPE:
				{
					m_Values[i] = boost::shared_ptr<IArrayPtr>();
					break;
				}
			case OBJECT_B_TYPE:
				{
					m_Values[i] = boost::shared_ptr<IObjectPtr>();
					break;
				}
			case CLASS_B_TYPE:
				{
					m_Values[i] = boost::shared_ptr<IClassPtr>();
					break;
				}
			default:
				{
					throw InternalErrorException(L"Unexpected basic type");
				}
			}
		}
	}

	ArrayImpl::~ArrayImpl(void)
	{
	}

	inline void ArrayImpl::checkBoundsAndType(int idx, basic_type basicType) const
	{
		if ((idx < 0) || (idx >= m_Length))
		{
			throw IndexOutOfBoundsException(L"Invalid index");
		}
		else if (m_BasicType != basicType)
		{
			throw InvalidTypeException(L"Invalid type");
		}
	}

	basic_type ArrayImpl::getBasicType() const
	{
		return m_BasicType;
	}

	int ArrayImpl::getLength() const
	{
		return m_Length;
	}

	void ArrayImpl::assignAt(int idx, IVariable& var)
	{
		switch (var.getBasicType())
		{
		case INTEGER_B_TYPE:
			{
				setIntegerAt(idx, var.getInteger());
				break;
			}
		case FLOAT_B_TYPE:
			{
				setFloatAt(idx, var.getFloat());
				break;
			}
		case STRING_B_TYPE:
			{
				setStringAt(idx, var.getString());
				break;
			}
		case ARRAY_B_TYPE:
			{
				setArrayAt(idx, var.getArray());
				break;
			}
		case OBJECT_B_TYPE:
			{
				setObjectAt(idx, var.getObject());
				break;
			}
		case CLASS_B_TYPE:
			{
				setClassAt(idx, var.getClass());
				break;
			}
		default:
			{
				throw InternalErrorException(L"Unexpected basic type");
			}
		}
	}

	int ArrayImpl::getIntegerAt(int idx) const
	{
		checkBoundsAndType(idx, INTEGER_B_TYPE);

		return *((int*) m_Values[idx].get());
	}

	void ArrayImpl::setIntegerAt(int idx, int value)
	{
		checkBoundsAndType(idx, INTEGER_B_TYPE);

		*((int*) m_Values[idx].get()) = value;
	}

	float ArrayImpl::getFloatAt(int idx) const
	{
		checkBoundsAndType(idx, FLOAT_B_TYPE);

		return *((float*) m_Values[idx].get());
	}

	void ArrayImpl::setFloatAt(int idx, float value)
	{
		checkBoundsAndType(idx, FLOAT_B_TYPE);

		*((float*) m_Values[idx].get()) = value;
	}

	wstring& ArrayImpl::getStringAt(int idx) const
	{
		checkBoundsAndType(idx, STRING_B_TYPE);

		return *((wstring*) m_Values[idx].get());
	}

	void ArrayImpl::setStringAt(int idx, const wstring& value)
	{
		checkBoundsAndType(idx, STRING_B_TYPE);

		*((wstring*) m_Values[idx].get()) = value;
	}

	IArrayPtr ArrayImpl::getArrayAt(int idx) const
	{
		checkBoundsAndType(idx, ARRAY_B_TYPE);

		return boost::static_pointer_cast<IArray>(m_Values[idx]);
	}

	void ArrayImpl::setArrayAt(int idx, const IArrayPtr& pValue)
	{
		checkBoundsAndType(idx, ARRAY_B_TYPE);

		m_Values[idx] = pValue;
	}

	IObjectPtr ArrayImpl::getObjectAt(int idx) const
	{
		checkBoundsAndType(idx, OBJECT_B_TYPE);

		return boost::static_pointer_cast<IObject>(m_Values[idx]);
	}

	void ArrayImpl::setObjectAt(int idx, const IObjectPtr& pValue)
	{
		checkBoundsAndType(idx, OBJECT_B_TYPE);

		m_Values[idx] = pValue;
	}

	IClassPtr ArrayImpl::getClassAt(int idx) const
	{
		checkBoundsAndType(idx, CLASS_B_TYPE);

		return boost::static_pointer_cast<IClass>(m_Values[idx]);
	}

	void ArrayImpl::setClassAt(int idx, const IClassPtr& pValue)
	{
		checkBoundsAndType(idx, CLASS_B_TYPE);

		m_Values[idx] = pValue;
	}
}