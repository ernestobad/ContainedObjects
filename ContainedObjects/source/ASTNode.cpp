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
		m_FileName = Engine::getInstance()->getCurrentFile();
	}

	ASTNode::~ASTNode(void)
	{
	}
}