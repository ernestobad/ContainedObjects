#pragma once

#include "ContextEntry.h"
#include "Context.h"
#include "ast_types.h"

namespace COBJ
{
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

		StaticContextEntry(const ClassDefPtr& pClassDef);
		StaticContextEntry(const InterfaceDefPtr& pInterfaceDef);
		StaticContextEntry(const VariableDeclDefPtr& pVariableDef);
		StaticContextEntry(const FormalParamDefPtr& pFormalParamDef);

		virtual ~StaticContextEntry(void);

		static_ctx_entry_type getStaticEntryType() const;

		bool getClass(ClassDefPtr& pClassDef) const;

		bool getInterface(InterfaceDefPtr& pInterfaceDef) const;

		bool getVariable(VariableDeclDefPtr& pVariableDef) const;

		bool getFormalParam(FormalParamDefPtr& pFormalParamDef) const;

		const std::wstring& getName() const;

	private:
		static_ctx_entry_type m_EntryType;
		boost::shared_ptr<void> m_pEntry;
		std::wstring m_Name;
	};
}
