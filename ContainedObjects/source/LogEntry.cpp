#include "platform.h"
#include "LogEntry.h"
#include "message_code.h"

namespace COBJ
{
	LogEntry::LogEntry(
		const std::wstring& file,
		int line,
		int charPosition,
		message_code messageCode,
		const std::wstring& message)
	{
		m_File = file;
		m_Line = line;
		m_CharPosition = charPosition;
		m_MessageCode = messageCode;
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

		switch (msg::getLevel(m_MessageCode))
		{
		case msg::ERR:
			strLevel = L"ERROR";
			break;
		case msg::WARN:
			strLevel = L"WARN";
			break;
		case msg::INFO:
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