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

using namespace COBJ;
using namespace std;

BOOST_AUTO_TEST_SUITE(literal_tests)

BOOST_AUTO_TEST_CASE(string_literal_test)
{
	list<const wstring> fileList;
	fileList.push_back(L"test_files/test_stringliteral.cbj");

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
		BOOST_REQUIRE(pEngine->getClass(L"Huh", pClass));

		BOOST_CHECK(!pClass->hasStaticVariable(L"x"));

		map<const wstring, IVariablePtr> params;
		IObjectPtr pObject;
		pClass->newObject(params, pObject);

		BOOST_CHECK(pObject->hasMemberVariable(L"w"));
		const IVariablePtr pWVar = pObject->getMemberVariable(L"w");
		BOOST_CHECK_EQUAL(pWVar->getString().compare(L"\x00E1\x00E9\x00FC"), 0);

		BOOST_CHECK(pObject->hasMemberVariable(L"x"));
		const IVariablePtr pXVar = pObject->getMemberVariable(L"x");
		BOOST_CHECK_EQUAL(pXVar->getString().compare(L"blah1FA1asdsd"), 0);

		BOOST_CHECK(pObject->hasMemberVariable(L"y"));
		const IVariablePtr pYVar = pObject->getMemberVariable(L"y");
		BOOST_CHECK_EQUAL(pYVar->getString().compare(L""), 0);

		BOOST_CHECK(pObject->hasMemberVariable(L"z"));
		const IVariablePtr pZVar = pObject->getMemberVariable(L"z");
		BOOST_CHECK_EQUAL(pZVar->getString().compare(L" 1234567890{};\"*^"), 0);
	}
	catch (exception&)
	{
		BOOST_FAIL("Unexpected Exception");
	}
}

BOOST_AUTO_TEST_CASE(numeric_literal_test)
{
	list<const wstring> fileList;
	fileList.push_back(L"test_files/test_numericliteral.cbj");

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
		BOOST_REQUIRE(pEngine->getClass(L"Huh", pClass));

		map<const wstring, IVariablePtr> params;
		IObjectPtr pObject;
		pClass->newObject(params, pObject);

		{
			BOOST_CHECK(pObject->hasMemberVariable(L"a"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"a");
			BOOST_CHECK_EQUAL(pVar->getInteger(), 1);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"b"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"b");
			BOOST_CHECK_EQUAL(pVar->getInteger(), -1);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"c"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"c");
			BOOST_CHECK_EQUAL(pVar->getInteger(), 1000);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"d"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"d");
			BOOST_CHECK_EQUAL(pVar->getInteger(), -1000);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"e"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"e");
			BOOST_CHECK_EQUAL(pVar->getFloat(), -1.0f);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"f"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"f");
			BOOST_CHECK_EQUAL(pVar->getFloat(), -.12f);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"g"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"g");
			BOOST_CHECK_EQUAL(pVar->getFloat(), 0.0f);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"h"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"h");
			BOOST_CHECK_EQUAL(pVar->getFloat(), 0.0f);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"i"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"i");
			BOOST_CHECK_EQUAL(pVar->getFloat(), 0.12345f);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"j"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"j");
			BOOST_CHECK_EQUAL(pVar->getFloat(), .12E3f);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"k"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"k");
			BOOST_CHECK_EQUAL(pVar->getFloat(), .12E-3f);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"l"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"l");
			BOOST_CHECK_EQUAL(pVar->getFloat(), .12f);
		}
		{
			BOOST_CHECK(pObject->hasMemberVariable(L"m"));
			const IVariablePtr pVar = pObject->getMemberVariable(L"m");
			BOOST_CHECK_EQUAL(pVar->getFloat(), .12f);
		}
	}
	catch (exception&)
	{
		BOOST_FAIL("Unexpected Exception");
	}
}

BOOST_AUTO_TEST_SUITE_END()
