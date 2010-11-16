#pragma once

#define LEVEL_MASK			0xF0000000
#define PHASE_MASK			0x0F000000
#define MODULE_MASK			0x00FF0000

namespace COBJ
{
	namespace msg
	{
		enum level
		{
			INFO	= 0x10000000,
			WARN	= 0x20000000,
			ERR		= 0x30000000
		};

		enum phase
		{
			PARSING		= 0x01000000,
			ANALYSIS	= 0x02000000
		};

		enum module
		{
			TYPE_INFER	= 0x00010000,
			OBJ_INIT	= 0x00020000,
			CTX_INIT	= 0x00030000
		};

		enum code
		{
			ErrAnaTypeInfer_NameNotInContext	= ERR|ANALYSIS|TYPE_INFER|1,
			ErrAnaTypeInfer_NotAMember			= ERR|ANALYSIS|TYPE_INFER|2,
			ErrAnaObjInit_MissingParam			= ERR|ANALYSIS|OBJ_INIT|1,
			ErrAnaObjInit_UnknownParam			= ERR|ANALYSIS|OBJ_INIT|2,
			ErrAnaObjInit_ClassNotFound			= ERR|ANALYSIS|OBJ_INIT|3,
			ErrAnaObjInit_NotAClass				= ERR|ANALYSIS|OBJ_INIT|4,
			ErrAnaObjInit_IncompTypes			= ERR|ANALYSIS|OBJ_INIT|5,
			ErrAnaCtxInit_ClassNameAlreadyExists	= ERR|ANALYSIS|CTX_INIT|1,
			ErrAnaCtxInit_IfaceNameAlreadyExists	= ERR|ANALYSIS|CTX_INIT|2,
			ErrAnaCtxInit_FParmNameAlreadyExsits	= ERR|ANALYSIS|CTX_INIT|3,
			ErrAnaCtxInit_VarNameAlreadyExsits		= ERR|ANALYSIS|CTX_INIT|4
		};

		level getLevel(code c);

		phase getPhase(code c);

		module getModule(code c);
	}

	typedef msg::code message_code;
}
