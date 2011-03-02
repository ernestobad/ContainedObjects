#include "platform.h"
#include "ArrayInitCheck.h"
#include "message_code.h"
#include "ASTNode.h"
#include "ArrayInitValueDef.h"
#include "ValueDef.h"
#include "SemanticAnalysis.h"
#include "Log.h"

namespace COBJ
{
	ArrayInitCheck::ArrayInitCheck(void)
	{
	}

	ArrayInitCheck::~ArrayInitCheck(void)
	{
	}

	void ArrayInitCheck::doCheck(
			const StaticContextPtr& pRootCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const
	{
		if (pNode->getASTNodeType() != ASTN_ARRAY_INIT_VALUE)
		{
			return;
		}

		ArrayInitValueDefPtr pArrayInit = boost::static_pointer_cast<ArrayInitValueDef>(pNode);

		const ArrayTypePtr pArrayType = boost::dynamic_pointer_cast<ArrayType>(pArrayInit->getInferredType());

		const std::list<ValueDefPtr>& values = pArrayInit->getValues();

		std::list<ValueDefPtr>::const_iterator it;

		for (it = values.begin(); it != values.end(); it++)
		{
			const ValueDefPtr pValue = *it;
			const TypePtr& pValueType = pValue->getInferredType();

			if (!SemanticAnalysis::isTypeAssignableFrom(
					pArrayType->getChildType(),
					pValueType,
					pRootCtx))
			{
				boost::wformat f(L"Can't convert from %1% to %2%.");
				f % pValueType->toString() % pArrayType->toString();
				pLog->log(*pValue, msg::ErrAnaArrayInit_IncompTypes, f.str());
				continue;
			}
		}
	}
}