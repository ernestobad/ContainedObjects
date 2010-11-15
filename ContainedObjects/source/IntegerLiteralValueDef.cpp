#include "platform.h"
#include "IntegerLiteralValueDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "exceptions.h"

namespace COBJ
{
	IntegerLiteralValueDef::IntegerLiteralValueDef(void)
		: LiteralValueDef(INTEGER_LITERAL)
	{
	}

	IntegerLiteralValueDef::IntegerLiteralValueDef(const pANTLR3_BASE_TREE node)
		: LiteralValueDef(INTEGER_LITERAL, node)
	{
		assert(node->getType(node) == N_INT_LITERAL);
		assert(node->getChildCount(node) == 1);

		pANTLR3_BASE_TREE n = (pANTLR3_BASE_TREE) node->getChild(node, 0);

		assert(n->getType(n) == INTL);

		wchar_t* szStr = (wchar_t*) n->getText(n)->chars;
		
		int value;

		try
		{
			value = boost::lexical_cast<int, wchar_t*>(szStr);
		}
		catch (const std::exception&)
		{
			boost::wformat f(L"Invalid integer value: %1% at line %2%");
			f % szStr % node->getLine(node);
			ParserException e(f.str());
			throw e;
		}

		m_IntValue = value;
	}

	IntegerLiteralValueDef::~IntegerLiteralValueDef(void)
	{
	}
}
