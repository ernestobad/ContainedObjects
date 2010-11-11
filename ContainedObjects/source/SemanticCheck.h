#pragma once

namespace COBJ
{
	enum semantic_check_type
	{
		CLASS_CHECK
	};

	class SemanticCheck
	{
	public:
		virtual ~SemanticCheck(void) { }

		virtual const semantic_check_type getType() const = 0;
	};
}