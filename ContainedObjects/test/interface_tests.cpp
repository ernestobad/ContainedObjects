#include "platform.h"

#include <boost/test/unit_test.hpp>

#include "../source/runtime_types.h"
#include "../source/IEngine.h"
#include "../source/IObject.h"
#include "../source/IVariable.h"
#include "../source/IClass.h"
#include "../source/Engine.h"
#include "../source/exceptions.h"
#include "../source/ILog.h"
#include "../source/IArray.h"
#include "../source/Type.h"
#include "../source/VariableImpl.h"

using namespace COBJ;
using namespace std;

BOOST_AUTO_TEST_SUITE(interface_tests)

BOOST_AUTO_TEST_CASE(interface_test)
{
	list<const wstring> fileList;
	fileList.push_back(L"test_files/test_interface4.cbj");
	fileList.push_back(L"test_files/test_interface2.cbj");
	fileList.push_back(L"test_files/test_interface1.cbj");
	fileList.push_back(L"test_files/test_interface3.cbj");

	list<IClassPtr> nativeClasses;
	IEnginePtr pEngine;
	ILogPtr pLog;

	try
	{
		CreateEngine(nativeClasses, pEngine);
		if (!pEngine->parseFiles(fileList))
		{
			pEngine->getLog(pLog);
			pLog->printAll(wcerr);
			BOOST_FAIL("parsing failed");
		}

		IClassPtr pHahClass;
		
		if (!pEngine->getClass(L"Hah", pHahClass))
		{
			BOOST_FAIL("couldn't retrieve class");
		}

		map<const wstring, IVariablePtr> hahClassParams;

		IVariablePtr pXParamVar(new VariableImpl(STRING_B_TYPE));
		pXParamVar->setString(L"xyz");

		hahClassParams[L"x"] = pXParamVar;

		IObjectPtr pHahObj;

		pHahClass->newObject(hahClassParams, pHahObj);

		if (pHahObj.get() == NULL)
		{
			BOOST_FAIL("Couldn't instantate class");
		}

		IClassPtr pHeheClass;
		
		if (!pEngine->getClass(L"Hehe", pHeheClass))
		{
			BOOST_FAIL("couldn't retrieve class");
		}

		map<const wstring, IVariablePtr> classParams;

		IObjectPtr pHeheObj;

		pHeheClass->newObject(classParams, pHeheObj);

		BOOST_REQUIRE(pHeheObj->hasMemberVariable(L"x"));
		const IVariablePtr& pXVar = pHeheObj->getMemberVariable(L"x");
		BOOST_CHECK(pXVar->getString() == L"hehe");

		BOOST_REQUIRE(pHeheObj->hasMemberVariable(L"s"));
		const IVariablePtr& pSVar = pHeheObj->getMemberVariable(L"s");
		wstring& xstr = pSVar->getString();
		BOOST_CHECK(xstr == L"z");
	}
	catch (COBJException& e)
	{
		e.printStackTrace(wcerr);
		BOOST_FAIL("Unexpected Exception");
	}
}

BOOST_AUTO_TEST_CASE(interface_err1_test)
{
	list<const wstring> fileList;
	fileList.push_back(L"test_files/test_interface4.cbj");
	fileList.push_back(L"test_files/test_interface2.cbj");
	fileList.push_back(L"test_files/test_interface1_err1.cbj");
	fileList.push_back(L"test_files/test_interface3.cbj");

	list<IClassPtr> nativeClasses;
	IEnginePtr pEngine;
	ILogPtr pLog;

	try
	{
		CreateEngine(nativeClasses, pEngine);
		if (pEngine->parseFiles(fileList))
		{
			BOOST_FAIL("error expected");
		}

		pEngine->getLog(pLog);

		// TODO: tests error codes
	}
	catch (COBJException& e)
	{
		e.printStackTrace(wcerr);
		BOOST_FAIL("Unexpected Exception");
	}
}

BOOST_AUTO_TEST_CASE(interface_err2_test)
{
	list<const wstring> fileList;
	fileList.push_back(L"test_files/test_interface4.cbj");
	fileList.push_back(L"test_files/test_interface2.cbj");
	fileList.push_back(L"test_files/test_interface1_err2.cbj");
	fileList.push_back(L"test_files/test_interface3.cbj");

	list<IClassPtr> nativeClasses;
	IEnginePtr pEngine;
	ILogPtr pLog;

	try
	{
		CreateEngine(nativeClasses, pEngine);
		if (pEngine->parseFiles(fileList))
		{
			BOOST_FAIL("error expected");
		}

		pEngine->getLog(pLog);

		// TODO: tests error codes
	}
	catch (COBJException& e)
	{
		e.printStackTrace(wcerr);
		BOOST_FAIL("Unexpected Exception");
	}
}

BOOST_AUTO_TEST_CASE(interface_err3_test)
{
	list<const wstring> fileList;
	fileList.push_back(L"test_files/test_interface4.cbj");
	fileList.push_back(L"test_files/test_interface2.cbj");
	fileList.push_back(L"test_files/test_interface1_err3.cbj");
	fileList.push_back(L"test_files/test_interface3.cbj");

	list<IClassPtr> nativeClasses;
	IEnginePtr pEngine;
	ILogPtr pLog;

	try
	{
		CreateEngine(nativeClasses, pEngine);
		if (pEngine->parseFiles(fileList))
		{
			BOOST_FAIL("error expected");
		}

		pEngine->getLog(pLog);

		// TODO: tests error codes
	}
	catch (COBJException& e)
	{
		e.printStackTrace(wcerr);
		BOOST_FAIL("Unexpected Exception");
	}
}

BOOST_AUTO_TEST_SUITE_END()
