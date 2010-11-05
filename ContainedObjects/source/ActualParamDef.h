/*
 * ActualParamDef.h
 *
 *  Created on: Oct 22, 2010
 *      Author: Ernesto
 */

#pragma once

#include <antlr3defs.h>

namespace COBJ
{
	class ValueDef;

	class ActualParamDef {
	public:
		ActualParamDef();
		ActualParamDef(const pANTLR3_BASE_TREE node);
		virtual ~ActualParamDef();

		const std::wstring& getParamName() const
		{
			return m_ParamName;
		}

		void setParamName(const std::wstring& paramName)
		{
			m_ParamName = paramName;
		}

		const boost::shared_ptr<ValueDef>& getValue() const
		{
			return m_pValue;
		}

		void setValue(boost::shared_ptr<ValueDef>& pValue)
		{
			m_pValue = pValue;
		}

	private:
		std::wstring m_ParamName;
		boost::shared_ptr<ValueDef> m_pValue;
	};

}
