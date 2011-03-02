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
			CTX_INIT	= 0x00030000,
			VAR_DECL	= 0x00040000,
			CLASS_DEF	= 0x00050000,
			TYPE_CHECK	= 0x00060000,
			IFACE_DEF	= 0x00070000,
			ARRAY_INIT	= 0x00080000,
			CTX_CHECK	= 0x00090000
		};

		enum code
		{
			ErrAnaTypeInfer_NameNotInContext	= ERR|ANALYSIS|TYPE_INFER|1,
			ErrAnaTypeInfer_NotAMember			= ERR|ANALYSIS|TYPE_INFER|2,
			ErrAnaTypeInfer_NonStaticVarRef		= ERR|ANALYSIS|TYPE_INFER|3,
			ErrAnaTypeInfer_NonStaticParamRef	= ERR|ANALYSIS|TYPE_INFER|4,
			ErrAnaTypeCheck_NameNotInContext	= ERR|ANALYSIS|TYPE_CHECK|1,
			ErrAnaTypeCheck_NameNotClassIface	= ERR|ANALYSIS|TYPE_CHECK|2,
			ErrAnaObjInit_MissingParam		= ERR|ANALYSIS|OBJ_INIT|1,
			ErrAnaObjInit_UnknownParam		= ERR|ANALYSIS|OBJ_INIT|2,
			ErrAnaObjInit_ClassNotFound		= ERR|ANALYSIS|OBJ_INIT|3,
			ErrAnaObjInit_NotAClass			= ERR|ANALYSIS|OBJ_INIT|4,
			ErrAnaObjInit_IncompTypes		= ERR|ANALYSIS|OBJ_INIT|5,
			ErrAnaCtxInit_ClassNameAlreadyExists	= ERR|ANALYSIS|CTX_INIT|1,
			ErrAnaCtxInit_FParmNameAlreadyExsits	= ERR|ANALYSIS|CTX_INIT|2,
			ErrAnaCtxCheck_StaticVarNameAlreadyExists	= ERR|ANALYSIS|CTX_CHECK|1,
			ErrAnaCtxCheck_InstanceVarNameAlreadyExists	= ERR|ANALYSIS|CTX_CHECK|2,
			ErrAnaVarDecl_IncompTypes			= ERR|ANALYSIS|VAR_DECL|1,
			ErrAnaClassDef_IfaceNotFound			= ERR|ANALYSIS|CLASS_DEF|1,
			ErrAnaClassDef_NotAnIface				= ERR|ANALYSIS|CLASS_DEF|2,
			ErrAnaClassDef_MissingIfaceParam		= ERR|ANALYSIS|CLASS_DEF|3,
			ErrAnaClassDef_ClassParamNotFoundIface	= ERR|ANALYSIS|CLASS_DEF|4,
			ErrAnaClassDef_IfaceParamIncompTypes	= ERR|ANALYSIS|CLASS_DEF|5,
			ErrAnaClassDef_MissingIfaceVar			= ERR|ANALYSIS|CLASS_DEF|6,
			ErrAnaClassDef_IfaceVarIncompTypes		= ERR|ANALYSIS|CLASS_DEF|7,
			ErrAnaClassDef_IfaceVarWrongScope		= ERR|ANALYSIS|CLASS_DEF|8,
			ErrAnaClassDef_UnassignedClassVar		= ERR|ANALYSIS|CLASS_DEF|9,
			ErrAnaIfaceDef_AssignedIfaceVar		= ERR|ANALYSIS|IFACE_DEF|1,
			ErrAnaArrayInit_IncompTypes		= ERR|ANALYSIS|ARRAY_INIT|1
		};

		level getLevel(code c);

		phase getPhase(code c);

		module getModule(code c);
	}

	typedef msg::code message_code;
}
