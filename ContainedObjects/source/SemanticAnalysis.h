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

		void addCheck(
			const ICheckPtr& pCheck);

		void analyze(
			const list<ClassDefBasePtr>& classes);

		const LogPtr& getLog() const;

		~SemanticAnalysis(void);

	private:

		void inferTypes(
			const std::list<ClassDefBasePtr>& classes,
			ConstStaticContextPtr& pRootCtx);

		void inferTypes(
			ValueDef& valueDef,
			ConstStaticContextPtr& pClassCtx);

		bool followPathElement(
			const Type& currentType,
			const StaticContext& rootCtx,
			const std::wstring& pathElement,
			TypePtr& pNextType);

		void newRootContext(
			ConstStaticContextPtr& pNewCtx,
			const std::list<ClassDefBasePtr>& classes);

		void newClassContext(
			ConstStaticContextPtr& pNewCtx,
			const ClassDefBasePtr& pClassDefBase,
			const ConstStaticContextPtr& pRootCtx);

		void newMemberContext(
			ConstStaticContextPtr& pNewCtx,
			const VariableDeclDefPtr& pVariableDef,
			const ConstStaticContextPtr& pClassCtx);

		void check(
			const ASTNodePtr& pNode,
			const ConstStaticContextPtr& pCtx);

		std::list<ICheckPtr> m_SemanticChecks;
		boost::shared_ptr<Log> m_pLog;
	};

	bool isTypeAssignableFrom(
		const TypePtr& pLType,
		const TypePtr& pRType,
		const ConstStaticContextPtr& pRootCtx);

}