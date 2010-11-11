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
		Context()
			: m_pParentContext()
		{
		}

		Context(const boost::shared_ptr<Context<E>>& pParentContext) 
			: m_pParentContext(pParentContext)
		{
		}

		virtual ~Context()
		{
		}

		virtual bool hasParent()
		{
			return m_pParentContext.get() != NULL;
		}

		virtual const boost::shared_ptr<Context<E>>& getParentContext()
		{
			return m_pParentContext;
		}

		virtual const Context<E>& getRootContext()
		{
			if (!hasParent())
			{
				return *this;
			}
			else
			{
				return m_pParentContext->getRootContext();
			}
		}

		virtual bool lookup(
			const std::wstring& name,
			boost::shared_ptr<const E>& pEntry,
			bool searchParents = true)
		{
			std::map<const std::wstring, boost::shared_ptr<const E>>::iterator it;

			it = m_Map.find(name);

			if (it == m_Map.end())
			{
				if (searchParents && this->hasParent())
				{
					return m_pParentContext->lookup(name, pEntry, searchParents);
				}

				return false;
			}

			pEntry = it->second;
			return true;
		}

		virtual bool addEntry(
			const boost::shared_ptr<const E>& pEntry)
		{
			std::map<const std::wstring, boost::shared_ptr<const E>>::iterator it;

			it = m_Map.find(pEntry->getName());

			if (it != m_Map.end())
			{
				return false;
			}

			m_Map[pEntry->getName()] = pEntry;

			return true;
		}

	private:
		boost::shared_ptr<Context<E>> m_pParentContext;
		std::map<const std::wstring, boost::shared_ptr<const E>> m_Map;
	};

}
