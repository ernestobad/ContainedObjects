#include "platform.h"
#include "InterfaceCheck.h"
#include "ASTNode.h"
#include "InterfaceDef.h"
#include "VariableDeclDef.h"
#include "Log.h"

namespace COBJ
{
	using namespace std;

	InterfaceCheck::InterfaceCheck(void)
	{
	}

	InterfaceCheck::~InterfaceCheck(void)
	{
	}

	void InterfaceCheck::doCheck(
			const StaticContextPtr& pCtx,
			const ASTNodePtr& pNode,
			const LogPtr& pLog) const
	{
		if (pNode->getASTNodeType() != ASTN_INTERFACE)
		{
			return;
		}

		InterfaceDefPtr pInterface = boost::static_pointer_cast<InterfaceDef>(pNode);

		const list<VariableDeclDefPtr>& vars = pInterface->getVariableDecls();

		list<VariableDeclDefPtr>::const_iterator it;

		for (it = vars.begin(); it != vars.end(); it++)
		{
			const VariableDeclDefPtr pVar = *it;

			if (pVar->getValue().get() != NULL)
			{
				boost::wformat f(L"Interface variable cannot be assigned %1%.");
				f % pVar->getName();
				pLog->log(*pVar, msg::ErrAnaIfaceDef_AssignedIfaceVar, f.str());
				continue;
			}
		}
		
	}
}