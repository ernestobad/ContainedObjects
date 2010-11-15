
#pragma once

namespace COBJ
{
	class IObject;

	class IArray
	{
	public:
        virtual ~IArray(){}

		virtual int getLength() const = 0;

		virtual Result getIntegerAt(int idx, int& intValue) const = 0;

		virtual Result setIntegerAt(int idx, int intValue) = 0;

		virtual Result getFloatAt(int idx, float& floatValue) const = 0;

		virtual Result setFloatAt(int idx, float floatValue) = 0;

		virtual Result getStringAt(int idx, std::wstring& string) const = 0;

		virtual Result setStringAt(int idx, const std::wstring& string) const = 0;

		virtual Result getObjectAt(int idx, boost::shared_ptr<IObject>& pObject) const = 0;

		virtual Result setObjectAt(int idx, const boost::shared_ptr<IObject>& pObject) const = 0;
	};
}
