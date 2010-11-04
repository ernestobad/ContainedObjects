#include "platform.h"
#include "RuntimeContextEntry.h"


namespace COBJ
{
	RuntimeContextEntry::RuntimeContextEntry(const boost::shared_ptr<IClass>& pClass)
		: m_EntryType(CLASS_RT_CTX_ENTRY), m_pEntry(pClass)
	{
	}

	RuntimeContextEntry::RuntimeContextEntry(const boost::shared_ptr<IInterface>& pInterface)
		: m_EntryType(INTERFACE_RT_CTX_ENTRY), m_pEntry(pInterface)
	{
	}

	RuntimeContextEntry::RuntimeContextEntry(const boost::shared_ptr<IVariable>& pVariable)
		: m_EntryType(VARIABLE_RT_CTX_ENTRY), m_pEntry(pVariable)
	{
	}

	RuntimeContextEntry::~RuntimeContextEntry()
	{
	}

	runtime_ctx_entry_type RuntimeContextEntry::getType() const
	{
		return m_EntryType;
	}

	Result RuntimeContextEntry::getClass(boost::shared_ptr<IClass>& pClass) const
	{
		if (m_EntryType != CLASS_RT_CTX_ENTRY)
		{
			return ErrorCode::InvalidType;
		}

		pClass = boost::static_pointer_cast<IClass>(m_pEntry);
		return ErrorCode::Ok;
	}

	Result RuntimeContextEntry::getInterface(boost::shared_ptr<IInterface>& pInterface) const
	{
		if (m_EntryType != INTERFACE_RT_CTX_ENTRY)
		{
			return ErrorCode::InvalidType;
		}

		pInterface = boost::static_pointer_cast<IInterface>(m_pEntry);
		return ErrorCode::Ok;
	}

	Result RuntimeContextEntry::getVariable(boost::shared_ptr<IVariable>& pVariable) const
	{
		if (m_EntryType != VARIABLE_RT_CTX_ENTRY)
		{
			return ErrorCode::InvalidType;
		}

		pVariable = boost::static_pointer_cast<IVariable>(m_pEntry);
		return ErrorCode::Ok;
	}
}
