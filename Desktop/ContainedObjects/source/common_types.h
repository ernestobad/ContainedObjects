
#pragma once

namespace COBJ
{
	class Log;
	typedef boost::shared_ptr<Log> LogPtr;
	typedef boost::shared_ptr<const Log> CLogPtr;

	class LogEntry;
	typedef boost::shared_ptr<LogEntry> LogEntryPtr;
	typedef boost::shared_ptr<const LogEntry> CLogEntryPtr;

	class LogMessage;
	typedef boost::shared_ptr<LogMessage> LogMessagePtr;
	typedef boost::shared_ptr<const LogMessage> CLogMessagePtr;
}