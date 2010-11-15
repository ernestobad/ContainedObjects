#pragma once

#include "Type.h"
#include "ReferenceType.h"
#include "ArrayType.h"
#include "ClassDef.h"
#include "StaticContextEntry.h"
#include "Context.h"
#include "ast_types.h"
#include "static_types.h"
#include "common_types.h"

namespace COBJ
{
	using namespace std;

	class SemanticAnalysis
	{
	public:
		SemanticAnalysis(const LogPtr& pLog);

		void addCheck(const ICheckPtr& pSemanticCheck);

		void analyze(
			std::list<ClassDefPtr> classes,
			std::list<InterfaceDefPtr> interfaces);

		static bool isTypeAssignableFrom(
			const ConstTypePtr& pLType,
			const ConstTypePtr& pRType,
			const ConstStaticContextPtr& pRootCtx)
		{
			if (*pLType == *pRType)
			{
				return true;
			}
			else if (pLType->getBasicType() != pRType->getBasicType())
			{
				return false;
			}
			else if (pLType->getBasicType() == OBJECT_B_TYPE)
			{
				ConstReferenceTypePtr& pLRefType = 
					boost::static_pointer_cast<const ReferenceType>(pLType);

				ConstReferenceTypePtr& pRRefType = 
					boost::static_pointer_cast<const ReferenceType>(pRType);

				const wstring& lTypeName = pLRefType->getReferenceTypeName();

				const wstring& rTypeName = pRRefType->getReferenceTypeName();

				ConstStaticContextEntryPtr pRCtxEntry;

				if (!pRootCtx->lookup(rTypeName, pRCtxEntry))
				{
					return false;
				}

				ClassDefPtr pRClass;
				if (!pRCtxEntry->getClass(pRClass))
				{
					// if rh type is an interface, then lh type must be the same interface
					// (ther is no interface inheritance), but we know that *pLType != *pRType
					// so the interfaces are not the same
					return false;
				}

				const list<const wstring>& interfaces = pRClass->getImplementedInterfaces();

				list<const wstring>::const_iterator it;

				for (it = interfaces.begin(); it != interfaces.end(); it++)
				{
					const wstring& ifaceName = *it;
					if (lTypeName == ifaceName)
					{
						return true;
					}
				}

				return false;
			}
			else if (pLType->getBasicType() == ARRAY_B_TYPE)
			{
				ConstArrayTypePtr pLArrayType = boost::static_pointer_cast<const ArrayType>(pLType);
				ConstArrayTypePtr pRArrayType = boost::static_pointer_cast<const ArrayType>(pRType);

				return isTypeAssignableFrom(
					pLArrayType->getChildType(),
					pRArrayType->getChildType(),
					pRootCtx);
			}
			else
			{
				return false;
			}
		}

		~SemanticAnalysis(void);

	private:

		void inferTypes(
			std::list<ClassDefPtr>& classes,
			ConstStaticContextPtr& pRootCtx);

		void inferTypes(
			ValueDef& valueDef,
			ConstStaticContextPtr& pClassCtx);

		bool followPathElement(
			const Type& currentType,
			const StaticContext& rootCtx,
			const std::wstring& pathElement,
			ConstTypePtr& pNextType);

		void initClassContext(
			StaticContext& newCtx,
			const ClassDef& pClassDef);

		std::list<ICheckPtr> m_SemanticChecks;
		boost::shared_ptr<Log> m_pLog;
	};

}