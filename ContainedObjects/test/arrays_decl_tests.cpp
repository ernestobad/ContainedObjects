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

BOOST_AUTO_TEST_SUITE(arrays_decl_tests)

BOOST_AUTO_TEST_CASE(array_init_test)
{
	list<const wstring> fileList;
	fileList.push_back(L"test_files/test_arrays_decl.cbj");

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

		IClassPtr pClass;
		
		if (!pEngine->getClass(L"Huh", pClass))
		{
			BOOST_FAIL("couldn't retrieve class");
		}

		map<const wstring, IVariablePtr> classParams;

		IObjectPtr pObj;

		pClass->newObject(classParams, pObj);

		if (pObj.get() == NULL)
		{
			BOOST_FAIL("Couln't instantate class");
		}

		const IVariablePtr& pVarA = pObj->getMemberVariable(L"a");
		IArrayPtr pArrA = pVarA->getArray();

		BOOST_CHECK(pArrA->getStringAt(0) == L"huh");
		BOOST_CHECK(pArrA->getStringAt(1) == L"heh");
		BOOST_CHECK_EQUAL(pArrA->getLength(), 2);

		const IVariablePtr& pVarB = pObj->getMemberVariable(L"b");
		IArrayPtr pArrB = pVarB->getArray();

		BOOST_CHECK(pArrB->getLength() == 0);

		const IVariablePtr& pVarC = pObj->getMemberVariable(L"c");
		IArrayPtr pArrC = pVarC->getArray();

		BOOST_CHECK(pArrC->getStringAt(0) == L"");
		BOOST_CHECK_EQUAL(pArrC->getLength(), 1);

		const IVariablePtr& pVarD = pObj->getMemberVariable(L"d");
		IArrayPtr pArrD = pVarD->getArray();

		BOOST_CHECK(pArrD->getIntegerAt(0) == 1);
		BOOST_CHECK(pArrD->getIntegerAt(1) == 2);
		BOOST_CHECK(pArrD->getIntegerAt(2) == 3);
		BOOST_CHECK_EQUAL(pArrD->getLength(), 3);

		const IVariablePtr& pVarE = pObj->getMemberVariable(L"e");
		IArrayPtr pArrE = pVarE->getArray();

		BOOST_CHECK(pArrE->getStringAt(0) == L"x");
		BOOST_CHECK_EQUAL(pArrE->getLength(), 1);
	}
	catch (COBJException& e)
	{
		e.printStackTrace(wcerr);
		BOOST_FAIL("Unexpected Exception");
	}
}

BOOST_AUTO_TEST_SUITE_END()
