/*
 * VariableDeclAssignDef.cpp
 *
 *  Created on: Oct 21, 2010
 *      Author: Ernesto
 */

#include "platform.h"
#include "VariableDeclAssignDef.h"

namespace COBJ
{

	VariableDeclAssignDef::VariableDeclAssignDef() :
		m_IsStatic(false), m_pDeclaredType(), m_Name(), m_pValue()
	{
	}

	VariableDeclAssignDef::~VariableDeclAssignDef() {
	}

}
