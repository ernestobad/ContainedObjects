#pragma once

#include "ContextEntry.h"

namespace COBJ
{
	class ClassDef;
	class InterfaceDef;
	class VariableDeclDef;
	class FormalParamDef;

	enum static_ctx_entry_type
	{
		CLASS_DEF_CTX_ENTRY,
		INTERFACE_DEF_CTX_ENTRY,
		VARIABLE_DEF_CTX_ENTRY,
		FORMAL_PARAM_DEF_CTX_ENTRY
	};

	class StaticContextEntry : public ContextEntry
	{
	public:

		StaticContextEntry(const boost::shared_ptr<ClassDef>& pClassDef);
		StaticContextEntry(const boost::shared_ptr<InterfaceDef>& pInterfaceDef);
		StaticContextEntry(const boost::shared_ptr<VariableDeclDef>& pVariableDef);
		StaticContextEntry(const boost::shared_ptr<FormalParamDef>& pFormalParamDef);

		virtual ~StaticContextEntry(void);

		static_ctx_entry_type getType() const;

		bool getClass(boost::shared_ptr<ClassDef>& pClassDef) const;

		bool getInterface(boost::shared_ptr<InterfaceDef>& pInterfaceDef) const;

		bool getVariable(boost::shared_ptr<VariableDeclDef>& pVariableDef) const;

		bool getFormalParam(boost::shared_ptr<FormalParamDef>& pFormalParamDef) const;

		const std::wstring& getName() const;

	private:
		static_ctx_entry_type m_EntryType;
		boost::shared_ptr<void> m_pEntry;
		std::wstring m_Name;
	};
}
