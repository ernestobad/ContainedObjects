#pragma once

namespace COBJ
{
	template <class E>
	class Context;

	class StaticContextEntry;

	typedef Context<StaticContextEntry> StaticContext;

	typedef boost::shared_ptr<StaticContext> StaticContextPtr;
	typedef boost::shared_ptr<const StaticContext> ConstStaticContextPtr;

	typedef boost::shared_ptr<StaticContextEntry> StaticContextEntryPtr;
	typedef boost::shared_ptr<const StaticContextEntry> ConstStaticContextEntryPtr;

	class ICheck;
	typedef boost::shared_ptr<ICheck> ICheckPtr;
	typedef boost::shared_ptr<const ICheck> ConstICheckPtr;
}