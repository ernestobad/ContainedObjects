#include "platform.h"
#include "message_code.h"

namespace COBJ
{
	namespace msg
	{
		level getLevel(code c)
		{
			return static_cast<level>(LEVEL_MASK & c);
		}

		phase getPhase(code c)
		{
			return static_cast<phase>(PHASE_MASK & c);
		}

		module getModule(code c)
		{
			return static_cast<module>(MODULE_MASK & c);
		}
	}
}