#pragma once

namespace COBJ
{
	enum static_ctx_type
	{
		CLASS_DEF,
		INTERFACE_DEF,
		VARIABLE_DECL_ASSIGN_DEF,
		VARIABLE_DECL_DEF,
		FORMAL_PARAM_DEF
	};

	class StaticContextEntry
	{
	public:
		StaticContextEntry(void);
		virtual ~StaticContextEntry(void);
	};
}
