#pragma once

#include "ContextEntry.h"


namespace COBJ
{
	class IClass;
	class IInterface;
	class IVariable;

	enum runtime_ctx_entry_type
	{
		CLASS_RT_CTX_ENTRY,
		INTERFACE_RT_CTX_ENTRY,
		VARIABLE_RT_CTX_ENTRY
	};

	class RuntimeContextEntry : public ContextEntry
	{
	public:
		RuntimeContextEntry(const boost::shared_ptr<IClass>& pClasss);
		RuntimeContextEntry(const boost::shared_ptr<IInterface>& pInterface);
		RuntimeContextEntry(const boost::shared_ptr<IVariable>& pVariable);

		virtual ~RuntimeContextEntry(void);

		runtime_ctx_entry_type getType() const;

		const std::wstring& getName() const;

		bool getClass(boost::shared_ptr<IClass>& pClass) const;

		bool getInterface(boost::shared_ptr<IInterface>& pInterface) const;

		bool getVariable(boost::shared_ptr<IVariable>& pVariable) const;

	private:
		runtime_ctx_entry_type m_EntryType;
		boost::shared_ptr<void> m_pEntry;
		std::wstring m_Name;
	};
}
