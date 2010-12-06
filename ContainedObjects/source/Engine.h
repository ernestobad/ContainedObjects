#pragma once

#include "IEngine.h"
#include "runtime_types.h"
#include "ast_types.h"
#include "common_types.h"

namespace COBJ
{
	using namespace std;

	class Engine : public IEngine
	{
	public:

		static const EnginePtr& getInstance()
		{
			if (s_pInstance == NULL)
			{
				s_pInstance = EnginePtr(new Engine());
			}

			return s_pInstance;
		}
		
		~Engine(void);

		void parseFiles(const list<const wstring>& filePaths);

		const std::wstring& getCurrentFile();

		bool getClass(
			const std::wstring& className,
			IClassPtr& pClass);

		const RuntimeContextPtr& getRootContext();

	private:
		Engine(void);

		static EnginePtr s_pInstance;

		void parseFile(const wstring& filePath);

		void initClasses();

		void initClass(const ClassDefBasePtr& pClassDefBase);

		RuntimeContextPtr m_pRootCtx;
		map<const wstring, ClassDefBasePtr> m_ClassDefMap;
		map<const wstring, IClassPtr> m_ClassesMap;
		LogPtr m_pLog;
		wstring m_CurrentFile;
	};	
}
