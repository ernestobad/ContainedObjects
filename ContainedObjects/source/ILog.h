
#pragma once

#include "message_code.h"
#include "ast_types.h"

namespace COBJ
{
	using namespace std;

	class ILog
    {
    public:
        virtual ~ILog(){}

		virtual bool hasErrors() const = 0;

		virtual bool hasMessages(int mask) const = 0;

		virtual bool hasMessage(message_code messageCode) const = 0;

		virtual void printAll(wostream& out) const = 0;
	};
}
