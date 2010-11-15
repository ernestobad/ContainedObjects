#pragma once

#include "common_types.h"

namespace COBJ
{
	class ASTNode;
	enum log_level;

	class Log
	{
	public:
		Log(void);
		~Log(void);

		void clear();

		bool hasErrors() const;

		void addError(
			const std::wstring& file, int line, int charPosition, const std::wstring& message);

		void addError(
			const ASTNode& node, const std::wstring& message);

		void addWarning(
			const std::wstring& file, int line, int charPosition, const std::wstring& message);

		void addWarning(
			const ASTNode& node, const std::wstring& message);

		void addInfo(
			const std::wstring& file, int line, int charPosition, const std::wstring& message);

		void addInfo(
			const ASTNode& node, const std::wstring& message);

		const std::list<ConstLogEntryPtr>& getEntries();

		void printAll();

	private:

		void addEntry(
			log_level level,
			const std::wstring& file,
			int line,
			int charPosition,
			const std::wstring& message);

		std::list<ConstLogEntryPtr> m_Entries;
		bool m_HasErrors;
	};
}
