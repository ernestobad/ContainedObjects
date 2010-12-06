#pragma once

#include "runtime_types.h"
#include "ast_types.h"
#include "IInterface.h"

namespace COBJ
{
	using namespace std;

	class InterfaceImpl : public IInterface
	{
	public:
		InterfaceImpl(IClassPtr& pInterfaceClass, IClass* pClass);
		InterfaceImpl(IClassPtr& pInterfaceClass, IObject* pObject);

		~InterfaceImpl(void);

		bool isNative() const;

		const IClassPtr& getClass() const;

		const IVariable& getVariable(unsigned int index) const;

	private:

		void initVars(IObject* pObject, IClass* pClass);

		const IClassPtr m_pClass;
		vector<IVariablePtr> m_Vars; 
	};
}