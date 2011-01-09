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

BOOST_AUTO_TEST_SUITE(reference_path_tests)

BOOST_AUTO_TEST_CASE(reference_path_test)
{
	list<const wstring> fileList;
	fileList.push_back(L"test_files/test_reference_path2.cbj");
	fileList.push_back(L"test_files/test_reference_path3.cbj");
	fileList.push_back(L"test_files/test_reference_path1.cbj");

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

		BOOST_REQUIRE(pHahObj->hasMemberVariable(L"x"));
		const IVariablePtr& pXVar = pHahObj->getMemberVariable(L"x");

		BOOST_CHECK(pXVar->getString() == L"xyz");
	}
	catch (COBJException& e)
	{
		e.printStackTrace(wcerr);
		BOOST_FAIL("Unexpected Exception");
	}
}

BOOST_AUTO_TEST_SUITE_END()
