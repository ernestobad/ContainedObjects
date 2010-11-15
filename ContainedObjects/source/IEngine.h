
#pragma once

namespace COBJ
{
	class IClass;
	class IInterface;
	class IVariable;
	class Type;

	class IEngine
    {
    public:
        virtual ~IEngine(){}

		virtual void parseFiles(
			const std::list<std::wstring>& filePaths) = 0;

		virtual void parseFile(
			const std::wstring& filePath) = 0;

		virtual bool getClass(
			const std::wstring& className,
			boost::shared_ptr<IClass>& pClass) = 0;

		virtual bool getInterface(
			const std::wstring& interfaceName,
			boost::shared_ptr<IInterface>& pInterface) = 0;
	};

	const void CreateEngine(
		const std::vector<boost::shared_ptr<IClass>>& nativeClasses,
		const std::vector<boost::shared_ptr<IInterface>>& nativeInterfaces,
		boost::shared_ptr<IEngine>& pEngine);
}
