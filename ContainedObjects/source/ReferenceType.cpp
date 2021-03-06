#include "platform.h"
#include "ReferenceType.h"
#include "exceptions.h"
#include "antlr/ContainedObjectsLexer.h"

namespace COBJ
{
	ReferenceType::ReferenceType(reference_type referenceType, const std::wstring& referenceTypeName)
		: Type((basic_type) referenceType), m_ReferenceTypeName(referenceTypeName)
	{
	}

	basic_type getReferenceBasicType(const pANTLR3_BASE_TREE node)
	{
		if (node->getType(node) == N_OBJECT_TYPE)
		{
			return (basic_type) OBJECT_REF_TYPE;
		}
		else if (node->getType(node) == N_CLASS_TYPE)
		{
			return (basic_type) CLASS_REF_TYPE;
		}
		else
		{
			std::wstring msg(L"Invalid node");
			InternalErrorException e(msg);
			throw e;
		}
	}

	ReferenceType::ReferenceType(const pANTLR3_BASE_TREE node)
		: Type(getReferenceBasicType(node), node)
	{
		assert(node->getChildCount(node) == 1);

		pANTLR3_BASE_TREE n = (pANTLR3_BASE_TREE) node->getChild(node, 0);
		assert(n->getType(n) == ID);

		m_ReferenceTypeName = (const wchar_t*) n->getText(n)->chars;
	}

	ReferenceType::~ReferenceType(void)
	{
	}

	reference_type ReferenceType::getReferenceType() const
	{
		return (reference_type) getBasicType();
	}

	const std::wstring& ReferenceType::getReferenceTypeName() const
	{
		return m_ReferenceTypeName;
	}

	std::wstring ReferenceType::toString() const
	{
		if (getReferenceType() == CLASS_REF_TYPE)
		{
			boost::wformat f(L"class<%1%>");
			f % m_ReferenceTypeName;
			return f.str();
		}
		else
		{
			return m_ReferenceTypeName;
		}
	}

	bool ReferenceType::operator==(const Type& type) const
	{
		if (type.getBasicType() != this->getBasicType())
		{
			return false;
		}

		const ReferenceType& refType = static_cast<const ReferenceType&>(type);

		return (refType.getReferenceTypeName() == this->getReferenceTypeName());
	}


}
