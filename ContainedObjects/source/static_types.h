#pragma once

namespace COBJ
{
	template <class E>
	class Context;

	class StaticContextEntry;

	typedef Context<StaticContextEntry> StaticContext;

	typedef boost::shared_ptr<StaticContext> StaticContextPtr;
	// typedef boost::shared_ptr<const StaticContext> CStaticContextPtr;

	typedef boost::shared_ptr<StaticContextEntry> StaticContextEntryPtr;
	typedef boost::shared_ptr<const StaticContextEntry> CStaticContextEntryPtr;

	class SemanticAnalysis;
	typedef boost::shared_ptr<SemanticAnalysis> SemanticAnalysisPtr;

	class ICheck;
	typedef boost::shared_ptr<ICheck> ICheckPtr;
	//typedef boost::shared_ptr<const ICheck> CICheckPtr;
}