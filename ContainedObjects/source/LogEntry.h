#pragma once

#include "message_code.h"

namespace COBJ
{
	class LogEntry
	{
	public:

		LogEntry(
			const std::wstring& fileName,
			int line,
			int charPosition,
			message_code messageCode,
			const std::wstring& message);

		~LogEntry(void);

		const std::wstring& getFile() const
		{
			return m_File;
		}

		int getLine() const
		{
			return m_Line;
		}

		int getCharPosition() const
		{
			return m_CharPosition;
		}

		message_code getMessageCode() const
		{
			return m_MessageCode;
		}

		const std::wstring& getMessage() const
		{
			return m_Message;
		}

		void printFormatedMessage() const;

		void formatMessage(std::wstring& message) const;

	private:
		std::wstring m_File;
		int m_Line;
		int m_CharPosition;
		message_code m_MessageCode;
		std::wstring m_Message;
	};
}