#pragma once

namespace COBJ
{
	enum log_level
	{
		ERROR_LEVEL = 2,
		WARNING_LEVEL = 1,
		INFO_LEVEL = 0
	};

	class LogEntry
	{
	public:

		LogEntry(
			log_level level,
			const std::wstring& fileName,
			int line,
			int charPosition,
			const std::wstring& message);

		~LogEntry(void);

		log_level getLevel() const
		{
			return m_Level;
		}

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

		const std::wstring& getMessage() const
		{
			return m_Message;
		}

		void printFormatedMessage() const;

		void formatMessage(std::wstring& message) const;

	private:
		log_level m_Level;
		std::wstring m_File;
		int m_Line;
		int m_CharPosition;
		std::wstring m_Message;
	};
}