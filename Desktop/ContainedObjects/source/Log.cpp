#include "platform.h"
#include "Log.h"
#include "LogEntry.h"
#include "ASTNode.h"
#include "message_code.h"

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

	bool Log::hasMessages(int mask) const
	{
		std::set<message_code>::const_iterator it;

		for (it = m_MessageCodes.begin(); it != m_MessageCodes.end(); it++)
		{
			message_code code = *it;
			if (code & mask)
			{
				return true;
			}
		}

		return false;
	}

	bool Log::hasMessage(message_code messageCode) const
	{
		if (m_MessageCodes.find(messageCode) == m_MessageCodes.end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void Log::clear()
	{
		m_Entries.clear();
		m_MessageCodes.clear();
		m_HasErrors = false;
	}

	void Log::printAll(wostream& out) const
	{
		std::list<CLogEntryPtr>::const_iterator it;

		for (it = m_Entries.begin(); it != m_Entries.end(); it++)
		{
			CLogEntryPtr pEntry = *it;
			pEntry->printFormatedMessage(out);
		}
	}

	const std::list<CLogEntryPtr>& Log::getEntries() const
	{
		return m_Entries;
	}

	void Log::log(
			const ASTNode& node,
			message_code messageCode, const std::wstring& message)
	{
		log(
			node.getFileName(),
			node.getLineNumer(),
			node.getCharPosition(),
			messageCode,
			message);
	}

	void Log::log(
		const std::wstring& file, int line, int charPosition,
		message_code messageCode, const std::wstring& message)
	{
		const CLogEntryPtr pEntry(
			new LogEntry(file, line, charPosition, messageCode, message));

		m_Entries.push_back(pEntry);
		m_MessageCodes.insert(messageCode);

		if (pEntry->getMessageCode() & msg::ERR)
		{
			m_HasErrors = true;
		}

		//pEntry->printFormatedMessage();
	}
}