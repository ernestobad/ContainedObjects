/*
 * FormalParamDef.h
 *
 *  Created on: Oct 20, 2010
 *      Author: Ernesto
 */

#pragma once

#include <antlr3defs.h>

namespace COBJ {

	class Type;

	class FormalParamDef
	{
	public:
		FormalParamDef();
		FormalParamDef(const pANTLR3_BASE_TREE node);
		virtual ~FormalParamDef();

		const Type* getType() const
		{
			return m_pType.get();
		}

		void setType(const boost::shared_ptr<Type>& pType)
		{
			m_pType = pType;
		}

		const std::wstring& getParamName() const
		{
			return m_ParamName;
		}

		void setParamName(const std::wstring& paramName)
		{
			m_ParamName = paramName;
		}

	private:
		boost::shared_ptr<Type> m_pType;
		std::wstring m_ParamName;
	};

}
