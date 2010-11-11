#include "platform.h"
#include "StringLiteralValueDef.h"
#include "antlr/ContainedObjectsLexer.h"
#include "exceptions.h"

#define START_STATE 1
#define NO_ESC_STATE 2
#define ESC_BEGIN_STATE 3
#define END_STATE 5

namespace COBJ
{
	StringLiteralValueDef::StringLiteralValueDef(void)
		: LiteralValueDef(STRING_LITERAL)
	{
	}

	StringLiteralValueDef::StringLiteralValueDef(const pANTLR3_BASE_TREE node)
		: LiteralValueDef(STRING_LITERAL)
	{
		assert(node->getType(node) == N_STRING_LITERAL);
		assert(node->getChildCount(node) == 1);

		pANTLR3_BASE_TREE n, c;

		n = (pANTLR3_BASE_TREE) node->getChild(node, 0);

		assert(n->getType(n) == STRINGL);

		wchar_t* szStr = (wchar_t*) n->getText(n)->chars;

		std::wstringbuf strBuff(std::ios_base::in);

		int state = START_STATE;
		for (wchar_t* pCurr = szStr; *pCurr != L'\0'; pCurr++)
		{
			wchar_t curr = *pCurr;
			switch (state)
			{
				case START_STATE:
					assert(curr == L'"');
					break;
				case NO_ESC_STATE:
					if (curr == L'\\')
					{
						state = ESC_BEGIN_STATE;
					}
					else if (curr == L'"')
					{
						state = END_STATE;
					}
					else
					{
						strBuff.sputc(curr);
					}
					break;
				case ESC_BEGIN_STATE:
					switch (curr)
					{
					case L'b':
						strBuff.sputc(L'\b');
						state = NO_ESC_STATE;
						break;
					case L't':
						strBuff.sputc(L'\t');
						state = NO_ESC_STATE;
						break;
					case L'n':
						strBuff.sputc(L'\n');
						state = NO_ESC_STATE;
						break;
					case L'f':
						strBuff.sputc(L'\f');
						state = NO_ESC_STATE;
						break;
					case L'r':
						strBuff.sputc(L'\r');
						state = NO_ESC_STATE;
						break;
					case L'"':
						strBuff.sputc(L'\"');
						state = NO_ESC_STATE;
						break;
					case L'\'':
						strBuff.sputc(L'\'');
						state = NO_ESC_STATE;
						break;
					case L'\\':
						strBuff.sputc(L'\\');
						state = NO_ESC_STATE;
						break;
					default:
						boost::wformat f(L"Unknown escape sequence \\%1% at line %2%");
						f % curr % node->getLine(node);
						ParserException e(f.str());
						throw e;
					}
					break;
				case END_STATE:
					assert(false);
					break;
				default:
					assert(false);
					break;
			}

			assert(state == END_STATE);
		}

		

		strBuff.str(m_StringValue);
	}

	StringLiteralValueDef::~StringLiteralValueDef(void)
	{
	}

}
