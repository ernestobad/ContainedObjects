#pragma once

#include "common_types.h"
#include "ast_types.h"
#include "message_code.h"
#include "Ilog.h"

namespace COBJ
{
	using namespace std;

	class Log : public ILog
	{
	public:
		Log(void);
		~Log(void);

		void clear();

		bool hasErrors() const;

		bool hasMessages(int mask) const;

		bool hasMessage(message_code messageCode) const;

		void log(
			const wstring& file, int line, int charPosition,
			message_code messageCode, const wstring& message);

		void log(
			const ASTNode& node,
			message_code messageCode, const wstring& message);

		const std::list<CLogEntryPtr>& getEntries() const;

		void printAll(wostream& out) const;

	private:

		list<CLogEntryPtr> m_Entries;
		set<message_code> m_MessageCodes;
		bool m_HasErrors;
	};
}
