#pragma once

#include "ContextEntry.h"
#include "runtime_types.h"

namespace COBJ
{
	using namespace std;

	enum runtime_ctx_entry_type
	{
		CLASS_RT_CTX_ENTRY,
		VARIABLE_RT_CTX_ENTRY
	};

	class RuntimeContextEntry : public ContextEntry
	{
	public:
		RuntimeContextEntry(const IClassPtr& pIClass);
		RuntimeContextEntry(const wstring& name, const IVariablePtr& pIVariable);

		virtual ~RuntimeContextEntry(void);

		runtime_ctx_entry_type getType() const;

		const wstring& getName() const;

		bool getClass(IClassPtr& pIClass) const;

		bool getVariable(IVariablePtr& pIVariable) const;

	private:
		runtime_ctx_entry_type m_EntryType;
		boost::shared_ptr<void> m_pEntry;
		wstring m_Name;
	};
}
