/*
 * Context.cpp
 *
 *  Created on: Oct 21, 2010
 *      Author: Ernesto
 */

#include "platform.h"
#include "Context.h"

namespace COBJ {

	template<class E>
	Context<E>::Context()
		: m_ParentContext(NULL)
	{
	}

	template<class E>
	Context<E>::Context(const boost::shared_ptr<Context<E>>& pParentContext)
		: m_ParentContext(pParentContext)
	{
	}

	template<class E>
	Context<E>::~Context()
	{
	}

	template<class E>
	Result Context<E>::lookup(
			const std::wstring& name,
			boost::shared_ptr<const E>& pEntry)
	{
		map<const std::wstring&, boost::shared_ptr<const E>>::iterator it;

		it = m_Map.find();

		if (it == m_Map.end())
		{
			return NoSuchElement;
		}

		pEntry = it->second;
		return ErrorCode::Ok;
	}

	template<class E>
	Result Context<E>::addEntry(
		const std::wstring& name,
		const boost::shared_ptr<const E>& pEntry)
	{
		map<const std::wstring&, boost::shared_ptr<const E>>::iterator it;

		it = m_Map.find();

		if (it != m_Map.end())
		{
			return ElementAlreadyExists;
		}

		mMap[name] = pEntry;
	}



}
