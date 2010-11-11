#pragma once

namespace COBJ
{

	class ContextEntry
	{
	public:
		virtual ~ContextEntry(void) {};

		virtual const std::wstring& getName() const = 0;
	};

}