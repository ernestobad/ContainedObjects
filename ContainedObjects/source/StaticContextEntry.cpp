#include "platform.h"
#include "StaticContextEntry.h"
#include "ClassDef.h"
#include "InterfaceDef.h"
#include "VariableDeclDef.h"
#include "FormalParamDef.h"

namespace COBJ
{
	StaticContextEntry::StaticContextEntry(const boost::shared_ptr<ClassDef>& pClassDef)
		: m_EntryType(CLASS_DEF_CTX_ENTRY), m_pEntry(pClassDef), m_Name(pClassDef->getClassName())
	{
	}

	StaticContextEntry::StaticContextEntry(const boost::shared_ptr<InterfaceDef>& pInterfaceDef)
		: m_EntryType(INTERFACE_DEF_CTX_ENTRY), m_pEntry(pInterfaceDef), m_Name(pInterfaceDef->getIntefaceName())
	{
	}

	StaticContextEntry::StaticContextEntry(const boost::shared_ptr<VariableDeclDef>& pVariableDef)
		: m_EntryType(VARIABLE_DEF_CTX_ENTRY), m_pEntry(pVariableDef), m_Name(pVariableDef->getName())
	{
	}

	StaticContextEntry::StaticContextEntry(const boost::shared_ptr<FormalParamDef>& pFormalParamDef)
		: m_EntryType(FORMAL_PARAM_DEF_CTX_ENTRY), m_pEntry(pFormalParamDef), m_Name(pFormalParamDef->getParamName())
	{
	}

	StaticContextEntry::~StaticContextEntry(void)
	{
	}

	static_ctx_entry_type StaticContextEntry::getType() const
	{
		return m_EntryType;
	}

	bool StaticContextEntry::getClass(boost::shared_ptr<ClassDef>& pClassDef) const
	{
		if (m_EntryType != CLASS_DEF_CTX_ENTRY)
			return false;

		pClassDef = boost::static_pointer_cast<ClassDef>(m_pEntry);
		return true;
	}

	bool StaticContextEntry::getInterface(boost::shared_ptr<InterfaceDef>& pInterfaceDef) const
	{
		if (m_EntryType != INTERFACE_DEF_CTX_ENTRY)
			return false;

		pInterfaceDef = boost::static_pointer_cast<InterfaceDef>(m_pEntry);
		return true;
	}

	bool StaticContextEntry::getVariable(boost::shared_ptr<VariableDeclDef>& pVariableDef) const
	{
		if (m_EntryType != VARIABLE_DEF_CTX_ENTRY)
			return false;

		pVariableDef = boost::static_pointer_cast<VariableDeclDef>(m_pEntry);
		return true;
	}

	bool StaticContextEntry::getFormalParam(boost::shared_ptr<FormalParamDef>& pFormalParamDef) const
	{
		if (m_EntryType != FORMAL_PARAM_DEF_CTX_ENTRY)
			return false;

		pFormalParamDef = boost::static_pointer_cast<FormalParamDef>(m_pEntry);
		return true;
	}

	const std::wstring& StaticContextEntry::getName() const
	{
		return m_Name;
	}
}
