#pragma once

#include "ValueDef.h"

class ActualParamDef;

namespace COBJ
{
	class ObjectInitValueDef : public ValueDef
	{
	public:
		ObjectInitValueDef(void);
		virtual ~ObjectInitValueDef(void);

		const std::wstring& getClassName() const
		{
			return m_ClassName;
		}

		void setClassName(const std::wstring& className)
		{
			m_ClassName = className;
		}

		const std::list<boost::shared_ptr<ActualParamDef>>& getActualParams()
		{
			return m_ActualParams;
		}

		void setActualParams(const std::list<boost::shared_ptr<ActualParamDef>>& actualParams)
		{
			m_ActualParams = actualParams;
		}

	private:
		std::wstring m_ClassName;
		std::list<boost::shared_ptr<ActualParamDef>> m_ActualParams;
	};
}