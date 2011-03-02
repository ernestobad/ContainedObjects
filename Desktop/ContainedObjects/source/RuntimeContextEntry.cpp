#include "platform.h"
#include "RuntimeContextEntry.h"
#include "IClass.h"
#include "ClassDef.h"
#include "IInterface.h"
#include "InterfaceDef.h"


namespace COBJ
{
	RuntimeContextEntry::RuntimeContextEntry(const boost::shared_ptr<IClass>& pClass)
		: m_EntryType(CLASS_RT_CTX_ENTRY), m_pEntry(pClass),
		m_Name(pClass->getDefinition()->getClassName())
	{
	}

	RuntimeContextEntry::RuntimeContextEntry(const wstring& name, const boost::shared_ptr<IVariable>& pVariable)
		: m_EntryType(VARIABLE_RT_CTX_ENTRY), m_Name(name), m_pEntry(pVariable)
	{
	}

	RuntimeContextEntry::~RuntimeContextEntry()
	{
	}

	runtime_ctx_entry_type RuntimeContextEntry::getType() const
	{
		return m_EntryType;
	}

	bool RuntimeContextEntry::getClass(boost::shared_ptr<IClass>& pClass) const
	{
		if (m_EntryType != CLASS_RT_CTX_ENTRY)
		{
			return false;
		}

		pClass = boost::static_pointer_cast<IClass>(m_pEntry);
		return true;
	}

	bool RuntimeContextEntry::getVariable(boost::shared_ptr<IVariable>& pVariable) const
	{
		if (m_EntryType != VARIABLE_RT_CTX_ENTRY)
		{
			return false;
		}

		pVariable = boost::static_pointer_cast<IVariable>(m_pEntry);
		return true;
	}

	const std::wstring& RuntimeContextEntry::getName() const
	{
		return m_Name;
	}
}
