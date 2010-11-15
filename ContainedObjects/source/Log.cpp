#include "platform.h"
#include "Log.h"
#include "LogEntry.h"
#include "ASTNode.h"

namespace COBJ
{
	Log::Log(void) : m_HasErrors(false)
	{
	}

	Log::~Log(void)
	{
	}

	bool Log::hasErrors() const
	{
		return m_HasErrors;
	}

	void Log::clear()
	{
		m_Entries.clear();
	}

	void Log::printAll()
	{
		std::list<ConstLogEntryPtr>::const_iterator it;

		for (it = m_Entries.begin(); it != m_Entries.end(); it++)
		{
			ConstLogEntryPtr pEntry = *it;
			pEntry->printFormatedMessage();
		}
	}

	const std::list<ConstLogEntryPtr>& Log::getEntries()
	{
		return m_Entries;
	}

	void Log::addError(
			const ASTNode& node, const std::wstring& message)
	{
		addEntry(
			ERROR_LEVEL,
			node.getFileName(),
			node.getLineNumer(),
			node.getCharPosition(),
			message);
	}

	void Log::addError(
		const std::wstring& file, int line, int charPosition, const std::wstring& message)
	{
		addEntry(ERROR_LEVEL, file, line, charPosition, message);
	}

	void Log::addWarning(
			const ASTNode& node, const std::wstring& message)
	{
		addEntry(
			WARNING_LEVEL,
			node.getFileName(),
			node.getLineNumer(),
			node.getCharPosition(),
			message);
	}

	void Log::addWarning(
		const std::wstring& file, int line, int charPosition, const std::wstring& message)
	{
		addEntry(WARNING_LEVEL, file, line, charPosition, message);
	}

	void Log::addInfo(
			const ASTNode& node, const std::wstring& message)
	{
		addEntry(
			INFO_LEVEL,
			node.getFileName(),
			node.getLineNumer(),
			node.getCharPosition(),
			message);
	}

	void Log::addInfo(
		const std::wstring& file, int line, int charPosition, const std::wstring& message)
	{
		addEntry(INFO_LEVEL, file, line, charPosition, message);
	}

	void Log::addEntry(
		log_level level,
		const std::wstring& file,
		int line,
		int charPosition,
		const std::wstring& message)
	{
		const ConstLogEntryPtr pEntry(
			new LogEntry(level, file, line, charPosition, message));

		m_Entries.push_back(pEntry);

		if (level == ERROR_LEVEL)
		{
			m_HasErrors = true;
		}

		pEntry->printFormatedMessage();
	}
}