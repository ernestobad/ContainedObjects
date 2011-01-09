#pragma once

#include "message_code.h"

namespace COBJ
{
	using namespace std;

	class LogEntry
	{
	public:

		LogEntry(
			const wstring& fileName,
			int line,
			int charPosition,
			message_code messageCode,
			const wstring& message);

		~LogEntry(void);

		const wstring& getFile() const
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

		void printFormatedMessage(wostream& out) const;

		void formatMessage(wstring& message) const;

	private:
		wstring m_File;
		int m_Line;
		int m_CharPosition;
		message_code m_MessageCode;
		wstring m_Message;
	};
}