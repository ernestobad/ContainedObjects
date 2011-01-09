#pragma once

#include "IEngine.h"
#include "runtime_types.h"
#include "static_types.h"
#include "ast_types.h"
#include "common_types.h"

namespace COBJ
{
	using namespace std;

	class Engine : public IEngine
	{
	public:
		
		Engine(void);
		~Engine(void);

		void setNativeClasses(const list<IClassPtr>& nativeClasses);

		bool parseFiles(const list<const wstring>& filePaths);

		void getLog(ILogPtr& pLog);

		bool getClass(
			const std::wstring& className,
			IClassPtr& pClass);

		const RuntimeContextPtr& getRootContext();

	private:
		
		void parseFile(const wstring& filePath);

		bool initClasses();

		void initClass(const ClassDefBasePtr& pClassDefBase);

		RuntimeContextPtr m_pRootCtx;
		map<const wstring, ClassDefBasePtr> m_ClassDefMap;
		map<const wstring, IClassPtr> m_ClassesMap;
		LogPtr m_pLog;
		wstring m_CurrentFile;
	};

}
