/*
 * Context.h
 *
 *  Created on: Oct 21, 2010
 *      Author: Ernesto
 */

#pragma once

namespace COBJ {

	template <class E>
	class Context {
	public:
		Context();
		Context(const boost::shared_ptr<Context<E>>& pParentContext);

		virtual ~Context();

		virtual Result lookup(
			const std::wstring& name,
			boost::shared_ptr<const E>& pEntry);

		virtual Result addEntry(
			const std::wstring& name,
			const boost::shared_ptr<const E>& pEntry);

	private:
		boost::shared_ptr<Context<E>> m_ParentContext;
		std::map<std::wstring, boost::shared_ptr<const E>> m_Map;
	};

}
