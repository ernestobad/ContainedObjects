/*
 * Error.h
 *
 *  Created on: Oct 20, 2010
 *      Author: Ernesto Badillo
 */

#pragma once

namespace COBJ
{

    namespace ErrorCode
    {
        enum Code
        {
            Ok = 0,
            ParseError,
            OutOfMemoryError,
            BadArgument,
            InternalError,
			InvalidType,
			NoSuchElement,
			ElementAlreadyExists,
			NotImplemented
        };
    }

    typedef ErrorCode::Code Result;
}
