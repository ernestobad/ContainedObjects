#pragma once

namespace COBJ
{
	template <class E>
	class Context;

	class RuntimeContextEntry;

	typedef Context<RuntimeContextEntry> RuntimeContext;

	typedef boost::shared_ptr<RuntimeContext> RuntimeContextPtr;
	typedef boost::shared_ptr<const RuntimeContext> ConstRuntimeContextPtr;

	typedef boost::shared_ptr<RuntimeContextEntry> RuntimeContextEntryPtr;
	typedef boost::shared_ptr<const RuntimeContextEntry> ConstRuntimeContextEntryPtr;

	class ClassImpl;
	typedef boost::shared_ptr<ClassImpl> ClassImplPtr;

	class ObjectImpl;
	typedef boost::shared_ptr<ObjectImpl> ObjectImplPtr;

	class VariableImpl;
	typedef boost::shared_ptr<VariableImpl> VariableImplPtr;

	class ArrayImpl;
	typedef boost::shared_ptr<ArrayImpl> ArrayImplPtr;

	class ILog;
	typedef boost::shared_ptr<ILog> ILogPtr;

	class IClass;
	typedef boost::shared_ptr<IClass> IClassPtr;

	class IVariable;
	typedef boost::shared_ptr<IVariable> IVariablePtr;

	class IArray;
	typedef boost::shared_ptr<IArray> IArrayPtr;

	class IInterface;
	typedef boost::shared_ptr<IInterface> IInterfacePtr;

	class IEngine;
	typedef boost::shared_ptr<IEngine> IEnginePtr;

	class IObject;
	typedef boost::shared_ptr<IObject> IObjectPtr;

	class Engine;
	typedef boost::shared_ptr<Engine> EnginePtr;
}