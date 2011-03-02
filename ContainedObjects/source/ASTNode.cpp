#include "platform.h"
#include "ASTNode.h"
#include "antlr/ContainedObjectsLexer.h"
#include "Engine.h"

namespace COBJ
{
	ASTNode::ASTNode(void)
	{
	}

	ASTNode::ASTNode(const pANTLR3_BASE_TREE node)
	{
		m_LineNumber = node->getLine(node);
		m_CharPosition = node->getCharPositionInLine(node);

		pANTLR3_BASE_TREE n = node;
		while ((n != NULL) && (n->u == NULL))
		{ 
			if (n->u != NULL)
			{
				m_FileName = (wchar_t*) n->u;
				node->u = n->u;
				break;
			}
			else
			{
				n = n->getParent(n);
			}
		}
	}

	ASTNode::~ASTNode(void)
	{
	}
}