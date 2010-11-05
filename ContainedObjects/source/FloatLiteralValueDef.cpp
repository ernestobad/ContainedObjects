#include "platform.h"
#include "FloatLiteralValueDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "exceptions.h"

namespace COBJ
{
	FloatLiteralValueDef::FloatLiteralValueDef(void)
		: LiteralValueDef(FLOAT_LITERAL)
	{
	}

	FloatLiteralValueDef::FloatLiteralValueDef(const pANTLR3_BASE_TREE node)
		: LiteralValueDef(FLOAT_LITERAL)
	{
		assert(node->getType(node) == N_FLOAT_LITERAL);
		assert(node->getChildCount(node) == 1);

		pANTLR3_BASE_TREE n = (pANTLR3_BASE_TREE) node->getChild(node, 0);

		assert(n->getType(n) == FLOATL);

		wchar_t* szStr = (wchar_t*) n->getText(n)->chars;

		float value;

		try
		{
			value = boost::lexical_cast<float, wchar_t*>(szStr);
		}
		catch (const std::exception&)
		{
			boost::wformat f(L"Invalid float value: %1% at line %2%");
			f % szStr % node->getLine(node);
			ParserException e(f.str());
			throw e;
		}

		m_FloatValue = value;
	}

	FloatLiteralValueDef::~FloatLiteralValueDef(void)
	{
	}
}
