
#pragma once

class basic_type;
class IObject;
class IArray;

namespace COBJ
{
	class IVariable
	{
	public:
        virtual ~IVariable(){}

		virtual basic_type getBasicType() = 0;

		virtual Result getInteger(int& value) const = 0;

		virtual Result setInteger(int value) = 0;

		virtual Result getFloat(float& value) const = 0;

		virtual Result setFloat(float value) = 0;

		virtual Result getString(std::wstring& value) const = 0;

		virtual Result setString(const std::wstring& value) const = 0;

		virtual Result getArray(boost::shared_ptr<IArray>& pValue) const = 0;

		virtual Result setArray(const boost::shared_ptr<IArray>& pValue) const = 0;

		virtual Result getObject(boost::shared_ptr<IObject>& pValue) const = 0;

		virtual Result setObject(const boost::shared_ptr<IObject>& pValue) const = 0;

		virtual Result getClass(boost::shared_ptr<IClass>& pValue) const = 0;

		virtual Result setClass(const boost::shared_ptr<IClass>& pValue) const = 0;
	};
}
