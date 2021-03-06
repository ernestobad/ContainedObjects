#pragma once

#include <antlr3defs.h>
#include "ast_types.h"

namespace COBJ
{
	enum ast_node_type
	{
		ASTN_ARRAY_TYPE,
		ASTN_PRIMITIVE_TYPE,
		ASTN_REFERENCE_TYPE,
		ASTN_OBJECT_INIT_VALUE,
		ASTN_REFERENCE_PATH_VALUE,
		ASTN_STRING_LITERAL_VALUE,
		ASTN_ARRAY_INIT_VALUE,
		ASTN_FLOAT_LITERAL_VALUE,
		ASTN_INTEGER_LITERAL_VALUE,
		ASTN_ACTUAL_PARAM,
		ASTN_CLASS,
		ASTN_FORMAL_PARAM,
		ASTN_INTERFACE,
		ASTN_VARIABLE_DECL
	};

	class ASTNode
	{
	public:
		ASTNode(void);
		ASTNode(const pANTLR3_BASE_TREE node);

		virtual ~ASTNode(void);

		virtual ast_node_type getASTNodeType() const = 0;

		virtual void getChildNodes(std::list<ASTNodePtr>& children) const = 0;

		virtual int getLineNumer() const
		{
			return m_LineNumber;
		}

		virtual void setLineNumber(int lineNumber)
		{
			m_LineNumber = lineNumber;
		}

		virtual int getCharPosition() const
		{
			return m_CharPosition;
		}

		virtual void setCharPosition(int charPosition)
		{
			m_CharPosition = charPosition;
		}

		virtual const std::wstring& getFileName() const
		{
			return m_FileName;
		}

		virtual void setFileName(const std::wstring& fileName)
		{
			m_FileName = fileName;
		}

	private:
		int m_LineNumber;
		int m_CharPosition;
		std::wstring m_FileName;
	};
}