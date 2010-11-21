#include "platform.h"

#include "IEngine.h"
#include "Engine.h"
#include "runtime_types.h"

using namespace COBJ;
using namespace std;

int main( int argc, const char* argv[] )
{
	wstring strFile = L"testprog3.cbj";
	list<const wstring> fileList;
	fileList.push_back(strFile);

	IEnginePtr pEngine = Engine::getInstance();
	pEngine->parseFiles(fileList);

	printf( "\nHello World\n\n" );
	printf( "Huh");
}
