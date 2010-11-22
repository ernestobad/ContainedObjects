#include "platform.h"
#include "exceptions.h"

namespace COBJ
{

	// COBJException //

	COBJException::COBJException(const std::wstring& message) 
		: m_Message(message), m_Cause()
	{
	}

	COBJException::COBJException(const std::wstring& message, const std::wstring& cause)
		: m_Message(message), m_Cause(cause)
	{
	}

#ifdef _WIN32
	COBJException::COBJException(const std::wstring& message, errno_t err)
		: m_Message(message), m_Cause()
	{
		wchar_t wct_error[256];
		if (_wcserror_s(wct_error, 256, err) != 0)
		{
			// TODO: log
			return;
		}

		m_Cause = wct_error;
	}

	COBJException::COBJException(const std::wstring& message, DWORD lastError)
	{
		LPWSTR pBuffer = NULL;

		::FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			lastError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&pBuffer,
			0,
			NULL );

		m_Cause = pBuffer;
		LocalFree(pBuffer);
	}
#endif

	COBJException::COBJException(const COBJException& e)
	{
		m_Message = e.getMessage();
		m_Cause = e.getCause();
	}

	COBJException::~COBJException(void)
	{
	}

	const std::wstring& COBJException::getMessage() const
	{
		return m_Message;
	}

	const std::wstring& COBJException::getCause() const
	{
		return m_Message;
	}

	// InternalErrorException //

	InternalErrorException::InternalErrorException(const std::wstring& message) 
		: COBJException(message)
	{
	}

	InternalErrorException::InternalErrorException(const std::wstring& message, const std::wstring& cause)
		: COBJException(message, cause)
	{
	}

	InternalErrorException::InternalErrorException(const InternalErrorException& e)
		: COBJException(e)
	{
	}

	InternalErrorException::~InternalErrorException(void)
	{
	}

	// IndexOutOfBoundsException //

	IndexOutOfBoundsException::IndexOutOfBoundsException(const std::wstring& message) 
		: COBJException(message)
	{
	}

	IndexOutOfBoundsException::IndexOutOfBoundsException(const std::wstring& message, const std::wstring& cause)
		: COBJException(message, cause)
	{
	}

	IndexOutOfBoundsException::IndexOutOfBoundsException(const IndexOutOfBoundsException& e)
		: COBJException(e)
	{
	}

	IndexOutOfBoundsException::~IndexOutOfBoundsException(void)
	{
	}

	// InvalidTypeException //

	InvalidTypeException::InvalidTypeException(const std::wstring& message) 
		: COBJException(message)
	{
	}

	InvalidTypeException::InvalidTypeException(const std::wstring& message, const std::wstring& cause)
		: COBJException(message, cause)
	{
	}

	InvalidTypeException::InvalidTypeException(const InvalidTypeException& e)
		: COBJException(e)
	{
	}

	InvalidTypeException::~InvalidTypeException(void)
	{
	}

	// IOException //

	IOException::IOException(const std::wstring& message) 
		: COBJException(message)
	{
	}

	IOException::IOException(const std::wstring& message, const std::wstring& cause)
		: COBJException(message, cause)
	{
	}

#ifdef _WIN32
	IOException::IOException(const std::wstring& message, errno_t err)
		: COBJException(message, err)
	{
	}
#endif

	IOException::IOException(const IOException& e)
		: COBJException(e)
	{
	}

	IOException::~IOException(void)
	{
	}

	// ParseException //

	ParserException::ParserException(const std::wstring& message)
		: COBJException(message)
	{
	}

	ParserException::ParserException(const std::wstring& message, const std::wstring& cause)
		: COBJException(message, cause)
	{
	}

#ifdef _WIN32
	ParserException::ParserException(const std::wstring& message, errno_t err)
		: COBJException(message, err)
	{
	}
#endif

	ParserException::ParserException(const ParserException& e)
		: COBJException(e)
	{
	}

	ParserException::~ParserException(void)
	{
	}

}