#include "platform.h"
#include "InterfaceImpl.h"
#include "IObject.h"
#include "IClass.h"
#include "InterfaceDef.h"
#include "IVariable.h"
#include "VariableDeclDef.h"
#include "ASTNode.h"
#include "exceptions.h"

namespace COBJ
{
	using namespace std;

	InterfaceImpl::InterfaceImpl(IClassPtr& pInterfaceClass, IClass* pClass)
		: m_pClass(pInterfaceClass)
	{
		initVars(NULL, pClass);
	}

	InterfaceImpl::InterfaceImpl(IClassPtr& pInterfaceClass, IObject* pObject)
		: m_pClass(pInterfaceClass)
	{
		initVars(pObject, NULL);
	}

	void InterfaceImpl::initVars(IObject* pObject, IClass* pClass)
	{
		const ClassDefBasePtr& pClassDefBase = m_pClass->getDefinition();

		if (pClassDefBase->getASTNodeType() != ASTN_INTERFACE) {
			throw RuntimeCheckException(L"Not an interface class");
		}

		const InterfaceDefPtr pInterfaceDef = boost::static_pointer_cast<InterfaceDef>(pClassDefBase);
		const list<VariableDeclDefPtr>& vars = pInterfaceDef->getVariableDecls();

		list<VariableDeclDefPtr>::const_iterator it;

		list<IVariablePtr> varsList;

		for (it = vars.begin(); it != vars.end(); it++)
		{
			const VariableDeclDefPtr& pVarDef = *it;
			const wstring& varName = pVarDef->getName();

			if (pObject != NULL && !pVarDef->isStatic()) {
				varsList.push_back(pObject->getMemberVariable(varName));
			}
			else if (pClass != NULL && pVarDef->isStatic()) {
				varsList.push_back(pClass->getStaticVariable(varName));
			}
		}

		m_Vars = vector<IVariablePtr>(varsList.begin(), varsList.end());
	}

	InterfaceImpl::~InterfaceImpl(void)
	{
	}

	bool InterfaceImpl::isNative() const
	{
		return false;
	}

	const IClassPtr& InterfaceImpl::getClass() const
	{
		return m_pClass;
	}

	const IVariable& InterfaceImpl::getVariable(unsigned int index) const
	{
		return *(m_Vars[index]);
	}
}