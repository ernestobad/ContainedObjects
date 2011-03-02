#include "platform.h"

#include "IEngine.h"
#include "IClass.h"
#include "Engine.h"
#include "runtime_types.h"
#include "exceptions.h"

using namespace COBJ;
using namespace std;
/**
int main( int argc, const char* argv[] )
{
	wstring strFile = L"testprog3.cbj";
	list<const wstring> fileList;
	fileList.push_back(strFile);

	list<IClassPtr> nativeClasses;
	IEnginePtr pEngine;

	CreateEngine(nativeClasses, pEngine);

	try
	{
		pEngine->parseFiles(fileList);
	}
	catch (ParserException& e)
	{
		wcout << L"Exception: " << e.getMessage();
	}
	catch (COBJException& e)
	{
		wcout << L"Exception: " << e.getMessage();
	}

	printf( "\nHello World\n\n" );
	printf( "Huh");
}
*/