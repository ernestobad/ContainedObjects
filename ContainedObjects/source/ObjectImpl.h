#pragma once

#include "IObject.h"
#include "runtime_types.h"
#include "ast_types.h"

namespace COBJ
{
	using namespace std;

	class ObjectImpl : public IObject
	{
	public:
		ObjectImpl(
			const IClass& iClass,
			const map<const wstring, IVariablePtr>& params,
			const RuntimeContextPtr& pClassContext);

		~ObjectImpl(void);

		bool isNative() const;

		const IClass& getClass() const;

		virtual bool implements(const wstring& interfaceName) const;

		virtual const IInterfacePtr& getInterface(const wstring& interfaceName) const;

		virtual bool hasMemberVariable(const wstring& varName) const;

		virtual const IVariablePtr& getMemberVariable(const wstring& varName) const;

	private:
		const IClass& m_IClass;
		map<const wstring, IVariablePtr> m_VarsMap;
		map<const wstring, IInterfacePtr> m_InterfacesMap;
	};
}