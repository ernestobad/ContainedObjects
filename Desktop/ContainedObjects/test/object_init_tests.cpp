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

using namespace COBJ;
using namespace std;

BOOST_AUTO_TEST_SUITE(object_init_tests)

BOOST_AUTO_TEST_CASE(object_init_test)
{
	list<const wstring> fileList;
	fileList.push_back(L"test_files/test_object_init3.cbj");
	fileList.push_back(L"test_files/test_object_init2.cbj");
	fileList.push_back(L"test_files/test_object_init1.cbj");

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

		map<const wstring, IVariablePtr> classParams;

		IObjectPtr pHahObj;

		pHahClass->newObject(classParams, pHahObj);

		if (pHahObj.get() == NULL)
		{
			BOOST_FAIL("Couldn't instantate class");
		}

		BOOST_REQUIRE(pHahObj->hasMemberVariable(L"heh"));
		const IVariablePtr& pHehVar = pHahObj->getMemberVariable(L"heh");
		IObjectPtr pHehObj = pHehVar->getObject();

		BOOST_REQUIRE(pHehObj->hasMemberVariable(L"ex"));
		const IVariablePtr& pExVar = pHehObj->getMemberVariable(L"ex");
		BOOST_CHECK(pExVar->getString() == L"abc");

		BOOST_REQUIRE(pHehObj->hasMemberVariable(L"ey"));
		const IVariablePtr& pEyVar = pHehObj->getMemberVariable(L"ey");
		BOOST_CHECK(pEyVar->getInteger() == 123);

		BOOST_REQUIRE(pHehObj->hasMemberVariable(L"ez"));
		const IVariablePtr& pEzVar = pHehObj->getMemberVariable(L"ez");
		BOOST_CHECK(pEzVar->getFloat() == 321.1f);

		BOOST_REQUIRE(pHahObj->hasMemberVariable(L"hih"));

		const IVariablePtr& pHihVar = pHahObj->getMemberVariable(L"hih");
		IObjectPtr pHihObj = pHihVar->getObject();

		BOOST_REQUIRE(pHihObj->hasMemberVariable(L"ix"));
		const IVariablePtr& pIxVar = pHihObj->getMemberVariable(L"ix");
		BOOST_CHECK(pIxVar->getString() == L"abc");

		IClassPtr pHihClass;
		if (!pEngine->getClass(L"Hih", pHihClass))
		{
			BOOST_FAIL("couldn't retrieve class");
		}

		BOOST_REQUIRE(pHihClass->hasStaticVariable(L"s"));
		const IVariablePtr& pSVar = pHihClass->getStaticVariable(L"s");

		BOOST_CHECK(pSVar->getString() == L"x");

		IClassPtr pHehClass;
		if (!pEngine->getClass(L"Heh", pHehClass))
		{
			BOOST_FAIL("couldn't retrieve class");
		}

		BOOST_REQUIRE(pHahObj->hasMemberVariable(L"hehClass"));
		const IVariablePtr& pHehClassVar = pHahObj->getMemberVariable(L"hehClass");
		IClassPtr pHehClass2 = pHehClassVar->getClass();

		BOOST_CHECK(pHehClass2.get() == pHehClass.get());

	}
	catch (COBJException& e)
	{
		e.printStackTrace(wcerr);
		BOOST_FAIL("Unexpected Exception");
	}
}

BOOST_AUTO_TEST_SUITE_END()
