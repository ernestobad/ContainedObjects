#pragma once

#include "IEngine.h"

namespace COBJ
{
	class Type;
	class IClass;
	class IInterface;

	class Engine : public IEngine
	{
	public:
		Engine(void);
		virtual ~Engine(void);

		virtual void parseFiles(const std::list<std::wstring>& filePaths);

		virtual void parseFile(const std::wstring& filePath);

		virtual Result getClass(const std::wstring& className, boost::shared_ptr<IClass>& pClass);

		virtual Result getInterface(const std::wstring& interfaceName, boost::shared_ptr<IInterface>& pInterface);

	private:
		std::list<boost::shared_ptr<IClass>> m_Classes;
		std::list<boost::shared_ptr<IInterface>> m_Interfaces;
	};

	
}
