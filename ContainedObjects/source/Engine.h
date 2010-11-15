#pragma once

#include "IEngine.h"

namespace COBJ
{
	class Type;
	class IClass;
	class IInterface;
	class Log;

	class Engine : public IEngine
	{
	public:

		static Engine* getInstance()
		{
			if (s_pInstance == NULL)
			{
				s_pInstance = new Engine();
			}

			return s_pInstance;
		}
		
		~Engine(void);

		void parseFiles(const std::list<std::wstring>& filePaths);

		void parseFile(const std::wstring& filePath);

		const std::wstring& getCurrentFile();

		bool getClass(
			const std::wstring& className,
			boost::shared_ptr<IClass>& pClass);

		bool getInterface(
			const std::wstring& interfaceName,
			boost::shared_ptr<IInterface>& pInterface);

	private:
		Engine(void);
		static Engine* s_pInstance;

		std::list<boost::shared_ptr<IClass>> m_Classes;
		std::list<boost::shared_ptr<IInterface>> m_Interfaces;
		boost::shared_ptr<Log> m_pLog;
		std::wstring m_CurrentFile;
	};	
}
