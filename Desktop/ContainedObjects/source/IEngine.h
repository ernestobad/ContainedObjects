
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

		virtual bool parseFiles(
			const list<const wstring>& filePaths) = 0;

		virtual bool getClass(
			const wstring& className,
			IClassPtr& pClass) = 0;

		virtual void getLog(ILogPtr& pLog) = 0;
	};

	void CreateEngine(
		const list<IClassPtr>& nativeClasses,
		IEnginePtr& pEngine);
}
