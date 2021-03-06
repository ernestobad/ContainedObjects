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
			: m_pParentContext(), m_IsStatic(false)
		{
		}

		Context(const boost::shared_ptr<Context<E>>& pParentContext, bool isStatic = false)
			: m_pParentContext(pParentContext), m_IsStatic(isStatic)
		{
		}

		virtual ~Context()
		{
		}

		virtual bool isStatic() const
		{
			return m_IsStatic;
		}

		virtual void setStatic(bool isStatic)
		{
			m_IsStatic = isStatic;
		}

		virtual bool hasParent() const
		{
			return m_pParentContext.get() != NULL;
		}

		virtual const boost::shared_ptr<Context<E>>& getParentContext() const
		{
			return m_pParentContext;
		}

		virtual bool getRootContext(boost::shared_ptr<Context<E>>& pRootCtx) const
		{
			if (!hasParent())
			{
				return false;
			}
			else
			{
				pRootCtx = m_pParentContext;
				m_pParentContext->getRootContext(pRootCtx);
				return true;
			}
		}

		virtual bool contains(const std::wstring& name, bool searchParents = true)
		{
			boost::shared_ptr<const E> pEntry;
			return lookup(name, pEntry, searchParents);
		}

		virtual bool lookup(
			const std::wstring& name,
			boost::shared_ptr<const E>& pEntry,
			bool searchParents = true) const
		{
			std::map<const std::wstring, boost::shared_ptr<const E>>::const_iterator it;

			it = m_Map.find(name);

			if (it == m_Map.end())
			{
				if (searchParents && hasParent())
				{
					return m_pParentContext->lookup(name, pEntry, searchParents);
				}
				else
				{
					return false;
				}
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

		virtual void clear()
		{
			m_Map.clear();
		}

	private:
		boost::shared_ptr<Context<E>> m_pParentContext;
		std::map<const std::wstring, boost::shared_ptr<const E>> m_Map;
		bool m_IsStatic;
	};

}
