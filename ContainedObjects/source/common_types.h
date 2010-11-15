
#pragma once

namespace COBJ
{
	class Value;
	typedef boost::shared_ptr<Value> ValuePtr;
	typedef boost::shared_ptr<const Value> ConstValuePtr;

	class Type;
	typedef boost::shared_ptr<Type> TypePtr;
	typedef boost::shared_ptr<const Type> ConstTypePtr;

	class PrimitiveType;
	typedef boost::shared_ptr<PrimitiveType> PrimitiveTypePtr;
	typedef boost::shared_ptr<const PrimitiveType> ConstPrimitiveTypePtr;

	class ReferenceType;
	typedef boost::shared_ptr<ReferenceType> ReferenceTypePtr;
	typedef boost::shared_ptr<const ReferenceType> ConstReferenceTypePtr;

	class ArrayType;
	typedef boost::shared_ptr<ArrayType> ArrayTypePtr;
	typedef boost::shared_ptr<const ArrayType> ConstArrayTypePtr;

	class Log;
	typedef boost::shared_ptr<Log> LogPtr;
	typedef boost::shared_ptr<const Log> ConstLogPtr;

	class LogEntry;
	typedef boost::shared_ptr<LogEntry> LogEntryPtr;
	typedef boost::shared_ptr<const LogEntry> ConstLogEntryPtr;

}