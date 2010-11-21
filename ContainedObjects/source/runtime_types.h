#pragma once

namespace COBJ
{
	class IClass;
	typedef boost::shared_ptr<IClass> IClassPtr;
	//typedef boost::shared_ptr<const IClass> ConstIClassPtr;

	class IVariable;
	typedef boost::shared_ptr<IVariable> IVariablePtr;
	//typedef boost::shared_ptr<const IVariable> ConstIVariablePtr;

	class IArray;
	typedef boost::shared_ptr<IArray> IArrayPtr;
	//typedef boost::shared_ptr<const IArray> ConstIArrayPtr;

	class IInterface;
	typedef boost::shared_ptr<IInterface> IInterfacePtr;
	//typedef boost::shared_ptr<const IInterface> ConstIInterfacePtr;

	class IEngine;
	typedef boost::shared_ptr<IEngine> IEnginePtr;
	//typedef boost::shared_ptr<const IEngine> ConstIEnginePtr;

	class IObject;
	typedef boost::shared_ptr<IObject> IObjectPtr;
	//typedef boost::shared_ptr<const IObject> ConstIObjectPtr;

	class Engine;
	typedef boost::shared_ptr<Engine> EnginePtr;
	//typedef boost::shared_ptr<const Engine> ConstEnginePtr;
}