#pragma once

#include "common_types.h"
#include "ast_types.h"
#include "message_code.h"

namespace COBJ
{

	class Log
	{
	public:
		Log(void);
		~Log(void);

		void clear();

		bool hasErrors() const;

		bool hasMessages(int mask) const;

		bool hasMessage(message_code messageCode) const;

		void log(
			const std::wstring& file, int line, int charPosition,
			message_code messageCode, const std::wstring& message);

		void log(
			const ASTNode& node,
			message_code messageCode, const std::wstring& message);

		const std::list<ConstLogEntryPtr>& getEntries() const;

		void printAll() const;

	private:

		std::list<ConstLogEntryPtr> m_Entries;
		std::set<message_code> m_MessageCodes;
		bool m_HasErrors;
	};
}
