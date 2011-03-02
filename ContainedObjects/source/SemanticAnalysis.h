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
		~SemanticAnalysis(void);

		void addCheck(
			const ICheckPtr& pCheck);

		void analyze(
			const list<ClassDefBasePtr>& classes);

		const LogPtr& getLog() const;

		static bool isTypeAssignableFrom(
			const TypePtr& pLType,
			const TypePtr& pRType,
			const StaticContextPtr& pRootCtx);

	private:

		void check(
			const ASTNodePtr& pNode,
			const StaticContextPtr& pCtx);

		void checkClassContext(
			const ClassDefBasePtr& pClassDefBase,
			const StaticContextPtr& pCtx);

		void checkInstanceContext(
			const ClassDefBasePtr& pClassDefBase,
			const StaticContextPtr& pCtx);

		void findStaticDependencies(
			const ClassDefBasePtr& pClassDefBase,
			const StaticContextPtr& pClassCtx,
			const ASTNodePtr& pNode);

		std::list<ICheckPtr> m_SemanticChecks;
		boost::shared_ptr<Log> m_pLog;
	};

	

}