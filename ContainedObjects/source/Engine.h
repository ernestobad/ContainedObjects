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

		void parseFile(const wstring& filePath);

		const std::wstring& getCurrentFile();

		bool getClass(
			const std::wstring& className,
			IClassPtr& pClass);

		bool getInterface(
			const std::wstring& interfaceName,
			IInterfacePtr& pInterface);

	private:
		Engine(void);
		static EnginePtr s_pInstance;

		list<IClassPtr> m_Classes;
		list<IInterfacePtr> m_Interfaces;
		LogPtr m_pLog;
		wstring m_CurrentFile;
	};	
}
