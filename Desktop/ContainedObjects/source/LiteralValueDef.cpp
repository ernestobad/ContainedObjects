#include "platform.h"
#include "LiteralValueDef.h"

namespace COBJ
{
	LiteralValueDef::LiteralValueDef(literal_type literalType, const pANTLR3_BASE_TREE node)
		: ValueDef(LITERAL, node), m_LiteralType(literalType)
	{
	}

	LiteralValueDef::LiteralValueDef(literal_type literalType)
		: ValueDef(LITERAL), m_LiteralType(literalType)
	{
	}

	LiteralValueDef::~LiteralValueDef(void)
	{
	}
}
