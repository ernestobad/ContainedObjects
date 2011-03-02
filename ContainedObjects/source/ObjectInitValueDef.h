#pragma once

#include "ValueDef.h"
#include <antlr3defs.h>
#include "ast_types.h"

namespace COBJ
{
	using namespace std;

	class ObjectInitValueDef : public ValueDef
	{
	public:
		ObjectInitValueDef(void);
		ObjectInitValueDef(const pANTLR3_BASE_TREE node);
		virtual ~ObjectInitValueDef(void);

		ast_node_type getASTNodeType() const
		{
			return ASTN_OBJECT_INIT_VALUE;
		}

		void getChildNodes(std::list<ASTNodePtr>& children) const;

		const wstring& getClassName() const
		{
			return m_ClassName;
		}

		void setClassName(const wstring& className)
		{
			m_ClassName = className;
		}

		const map<const wstring, ActualParamDefPtr>& getActualParamsMap() const
		{
			return m_ActualParamsMap;
		}

		void setActualParamsMap(const map<const wstring, ActualParamDefPtr>& actualParamsMap)
		{
			m_ActualParamsMap = actualParamsMap;
		}

	private:
		wstring m_ClassName;
		map<const wstring, ActualParamDefPtr> m_ActualParamsMap;
	};
}
