
#pragma once

#include "runtime_types.h"
#include "ast_types.h"

namespace COBJ
{
	using namespace std;

	class IEngine
    {
    public:
        virtual ~IEngine(){}

		virtual void parseFiles(
			const list<const wstring>& filePaths) = 0;

		virtual void parseFile(
			const wstring& filePath) = 0;

		virtual bool getClass(
			const wstring& className,
			IClassPtr& pClass) = 0;
	};

	const void CreateEngine(
		const vector<IClassPtr>& nativeClasses,
		IEnginePtr& pEngine);
}
