#include "platform.h"
#include "TypeCheck.h"
#include "Context.h"
#include "StaticContextEntry.h"
#include "Log.h"
#include "Type.h"
#include "ArrayType.h"
#include "ReferenceType.h"
#include "message_code.h"

namespace COBJ
{
	using namespace std;

	TypeCheck::TypeCheck(void)
	{
	}

	TypeCheck::~TypeCheck(void)
	{
	}

	void TypeCheck::doCheck(
			const StaticContextPtr& pCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const
	{
		if ((pNode->getASTNodeType() != ASTN_ARRAY_TYPE) &&
			(pNode->getASTNodeType() != ASTN_PRIMITIVE_TYPE) &&
			(pNode->getASTNodeType() != ASTN_REFERENCE_TYPE))
		{
			return;
		}

		TypePtr pType = boost::static_pointer_cast<Type>(pNode);

		StaticContextPtr pRootCtx = pCtx;
		pCtx->getRootContext(pRootCtx);

		switch (pType->getBasicType())
		{
		case FLOAT_B_TYPE:
		case INTEGER_B_TYPE:
		case STRING_B_TYPE:
		case ARRAY_B_TYPE:
			break;
		case OBJECT_B_TYPE:
		case CLASS_B_TYPE:
			{
				const ReferenceTypePtr pRefType = boost::static_pointer_cast<ReferenceType>(pType);
				const wstring& typeName = pRefType->getReferenceTypeName();

				CStaticContextEntryPtr pEntry;
				if (!pRootCtx->lookup(typeName, pEntry))
				{
					boost::wformat f(L"Name %1% not found in context");
					f % pEntry->getName();
					pLog->log(*pNode, msg::ErrAnaTypeCheck_NameNotInContext, f.str());
				}
				else if ((pEntry->getStaticEntryType() != CLASS_DEF_CTX_ENTRY) && 
					(pEntry->getStaticEntryType() != INTERFACE_DEF_CTX_ENTRY))
				{
					boost::wformat f(L"%1% is not a class or interface");
					f % pEntry->getName();
					pLog->log(*pNode, msg::ErrAnaTypeCheck_NameNotClassIface, f.str());
				}
			}
			break;
		default:
			assert(false);
			break;
		}
	}
}