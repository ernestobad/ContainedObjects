#include "platform.h"
#include "LogEntry.h"

namespace COBJ
{

	LogEntry::LogEntry(
		log_level level,
		const std::wstring& file,
		int line,
		int charPosition,
		const std::wstring& message)
	{
		m_Level = level;
		m_File = file;
		m_Line = line;
		m_CharPosition = charPosition;
		m_Message = message;
	}

	LogEntry::~LogEntry(void)
	{
	}

	void LogEntry::printFormatedMessage() const
	{
		std::wstring msg;
		formatMessage(msg);
		std::wcout << msg;
	}

	void LogEntry::formatMessage(std::wstring& message) const
	{
		std::wstring strLevel;

		switch (m_Level)
		{
		case ERROR_LEVEL:
			strLevel = L"ERROR";
			break;
		case WARNING_LEVEL:
			strLevel = L"WARN";
			break;
		case INFO_LEVEL:
			strLevel = L"INFO";
			break;
		default:
			assert(false);
		}

		boost::wformat f(L"%1% (%2%-%3%): %4% %5%");
		f % m_File % m_Line % m_CharPosition % strLevel % m_Message;
		message = f.str();
	}
}