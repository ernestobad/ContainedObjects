#include "platform.h"

#include "IEngine.h"
#include "Engine.h"

using namespace COBJ;

int main( int argc, const char* argv[] )
{
	std::wstring strFile = L"testprog3.cbj";
	std::list<std::wstring> fileList;
	fileList.push_back(strFile);

	IEngine* pEngine = new Engine();
	pEngine->parseFiles(fileList);

	printf( "\nHello World\n\n" );
	printf( "Huh");
}
