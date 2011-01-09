#include "platform.h"
#include "VariableDeclCheck.h"
#include "ASTNode.h"
#include "Log.h"
#include "Context.h"
#include "StaticContextEntry.h"
#include "VariableDeclDef.h"
#include "message_code.h"
#include "ValueDef.h"
#include "SemanticAnalysis.h"

namespace COBJ
{
	VariableDeclCheck::VariableDeclCheck(void)
	{
	}

	VariableDeclCheck::~VariableDeclCheck(void)
	{
	}

	void VariableDeclCheck::doCheck(
			const StaticContextPtr& pRootCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const
	{
		if (pNode->getASTNodeType() != ASTN_VARIABLE_DECL)
		{
			return;
		}

		VariableDeclDefPtr pVariableDecl = boost::static_pointer_cast<VariableDeclDef>(pNode);

		const TypePtr& pDeclaredType = pVariableDecl->getDeclaredType();

		const ValueDefPtr& pValue = pVariableDecl->getValue();

		if (pValue.get() == NULL)
		{
			return;
		}

		const TypePtr& pValueType = pValue->getInferredType();

		if (pValueType.get() == NULL)
		{
			// type inference failed
			assert(pLog->hasMessages(msg::ERR|msg::ANALYSIS|msg::TYPE_INFER));
			return;
		}

		if (!SemanticAnalysis::isTypeAssignableFrom(
					pDeclaredType,
					pValueType,
					pRootCtx))
		{
			boost::wformat f(L"Cannot convert value from %1% to %2%.");
			f % pValueType->toString() %  pDeclaredType->toString();
			pLog->log(*pVariableDecl, msg::ErrAnaVarDecl_IncompTypes, f.str());
			return;
		}

	}
}