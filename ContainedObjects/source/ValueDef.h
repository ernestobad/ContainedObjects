/*
 * ValueDef.h
 *
 *  Created on: Oct 21, 2010
 *      Author: Ernesto
 */

#pragma once

#include <antlr3defs.h>
#include "ASTNode.h"
#include "ast_types.h"
#include "common_types.h"

namespace COBJ {

	class Type;

	enum value_type
	{
		OBJECT_INIT, ARRAY_INIT, LITERAL, REFERENCE_PATH
	};

	class ValueDef : public ASTNode
	{
	public:
		ValueDef(value_type valueType);
		ValueDef(value_type valueType, const pANTLR3_BASE_TREE node);

		virtual ~ValueDef();

		virtual ast_node_type getASTNodeType() const = 0;

		const ConstTypePtr& getInferredType() const
		{
			return m_pInferredType;
		}

		void setInferredType(const ConstTypePtr& pInferredType)
		{
			m_pInferredType = pInferredType;
		}

		value_type getValueType() const
		{
			return m_ValueType;
		}

		void setValueType(const value_type valueType)
		{
			m_ValueType = valueType;
		}

	private:
		ConstTypePtr m_pInferredType;
		value_type m_ValueType;

	};

	void createValueDef(
				const pANTLR3_BASE_TREE node,
				ValueDefPtr& pType);
}
