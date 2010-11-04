#pragma once

class IClass;
class IInterface;
class IVariable;

namespace COBJ
{
	enum runtime_ctx_entry_type
	{
		CLASS_RT_CTX_ENTRY,
		INTERFACE_RT_CTX_ENTRY,
		VARIABLE_RT_CTX_ENTRY
	};

	class RuntimeContextEntry
	{
	public:
		RuntimeContextEntry(const boost::shared_ptr<IClass>& pClasss);
		RuntimeContextEntry(const boost::shared_ptr<IInterface>& pInterface);
		RuntimeContextEntry(const boost::shared_ptr<IVariable>& pVariable);

		virtual ~RuntimeContextEntry(void);

		runtime_ctx_entry_type getType() const;

		Result getClass(boost::shared_ptr<IClass>& pClass) const;

		Result getInterface(boost::shared_ptr<IInterface>& pInterface) const;

		Result getVariable(boost::shared_ptr<IVariable>& pVariable) const;

	private:
		runtime_ctx_entry_type m_EntryType;
		boost::shared_ptr<void> m_pEntry;
	};
}
