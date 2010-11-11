#pragma once

#include "Context.h"


namespace COBJ
{
	class SemanticCheck;
	class ClassDef;
	class InterfaceDef;
	class ValueDef;
	class StaticContextEntry;
	class Type;

	class SemanticAnalysis
	{
	public:
		SemanticAnalysis(void);

		void addCheck(const boost::shared_ptr<SemanticCheck>& pSemanticCheck);

		void analyze(
			std::list<boost::shared_ptr<ClassDef>> classes,
			std::list<boost::shared_ptr<InterfaceDef>> interfaces);

		~SemanticAnalysis(void);

	private:
		// TODO: these method's signarues changed in order to receive references
		// instead of shared_ptr refs. Implementations need to be updated.

		void inferTypes(
			std::list<boost::shared_ptr<ClassDef>>& classes,
			const Context<StaticContextEntry>& rootCtx);

		void inferTypes(
			const ValueDef& pValueDef,
			const Context<StaticContextEntry>& classCtx);

		bool followPath(
			const Type& currentType,
			const Context<StaticContextEntry>& rootCtx,
			const std::wstring& pathElement,
			boost::shared_ptr<Type>& pNextType);

		void initClassContext(
			Context<StaticContextEntry>& newCtx,
			const ClassDef& pClassDef);

		std::list<boost::shared_ptr<SemanticCheck>> semanticChecks;
	};

}