#include "platform.h"
#include "exceptions.h"

#ifdef _WIN32
#include <StackWalker.h>
#include "conversions.h"
#endif

namespace COBJ
{
	using namespace std;

#ifdef _WIN32
	class MyStackWalker : public StackWalker
	{
	public:
	  MyStackWalker() : StackWalker()
	  {
		  ShowCallstack();
	  }

	  const void getStackTrace(list<wstring>& stackTrace) const
	  {
		  list<wstring>::const_iterator it;

		  stackTrace.clear();

		  for (it = m_StackTrace.begin(); it != m_StackTrace.end(); it++)
		  {
			  stackTrace.push_back(*it);
		  }
	  }

	protected:

	  virtual void OnOutput(LPCSTR szText)
	  {
		  string st = szText;
		  wstring wst;
		  convertUTF8ToUTF16(st, wst);

		  m_StackTrace.push_back(wst);
	  }

	private:

		list<wstring> m_StackTrace;
	};
#endif

	// COBJException //

	COBJException::COBJException(const wstring& message) 
		: m_Message(message)
	{
		fillStackTrace();
	}

	COBJException::COBJException(const wstring& message, const wstring& cause)
		: m_Message(message), m_Cause(cause)
	{
		fillStackTrace();
	}

#ifdef _WIN32
	COBJException::COBJException(const wstring& message, errno_t err)
		: m_Message(message), m_Cause(), m_StackTrace()
	{
		wchar_t wct_error[256];
		if (_wcserror_s(wct_error, 256, err) != 0)
		{
			// TODO: log
			return;
		}

		m_Cause = wct_error;

		fillStackTrace();
	}

	COBJException::COBJException(const wstring& message, DWORD lastError)
		: m_Message(message), m_Cause(), m_StackTrace()
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

		fillStackTrace();
	}
#endif

	COBJException::COBJException(const COBJException& e)
	{
		m_Message = e.getMessage();
		m_Cause = e.getCause();
		m_StackTrace = e.m_StackTrace;
	}

	COBJException::~COBJException(void)
	{
	}

	void COBJException::printStackTrace(wostream& out) const
	{
		out << L"COBJException: " << getMessage() << L": " << getCause() << L"\n";

		list<wstring>::const_iterator it;

		for (it = m_StackTrace.begin(); it != m_StackTrace.end(); it++)
		{
			out << L"COBJException: " << *it << L"\n";
		}
	}

	void COBJException::fillStackTrace()
	{
#ifdef _WIN32
		MyStackWalker sw;
		sw.getStackTrace(m_StackTrace);
#endif
	}

	const wstring& COBJException::getMessage() const
	{
		return m_Message;
	}

	const wstring& COBJException::getCause() const
	{
		return m_Message;
	}

	// InternalErrorException //

	InternalErrorException::InternalErrorException(const wstring& message) 
		: COBJException(message)
	{
	}

	InternalErrorException::InternalErrorException(const wstring& message, const wstring& cause)
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

	// RuntimeCheckException // 

	RuntimeCheckException::RuntimeCheckException(const wstring& message) 
		: COBJException(message)
	{
	}

	RuntimeCheckException::RuntimeCheckException(const wstring& message, const wstring& cause)
		: COBJException(message, cause)
	{
	}

	RuntimeCheckException::RuntimeCheckException(const RuntimeCheckException& e)
		: COBJException(e)
	{
	}

	RuntimeCheckException::~RuntimeCheckException(void)
	{
	}

	// IndexOutOfBoundsException //

	IndexOutOfBoundsException::IndexOutOfBoundsException(const wstring& message) 
		: COBJException(message)
	{
	}

	IndexOutOfBoundsException::IndexOutOfBoundsException(const wstring& message, const wstring& cause)
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

	InvalidTypeException::InvalidTypeException(const wstring& message) 
		: COBJException(message)
	{
	}

	InvalidTypeException::InvalidTypeException(const wstring& message, const wstring& cause)
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

	IOException::IOException(const wstring& message) 
		: COBJException(message)
	{
	}

	IOException::IOException(const wstring& message, const wstring& cause)
		: COBJException(message, cause)
	{
	}

#ifdef _WIN32
	IOException::IOException(const wstring& message, errno_t err)
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

	ParserException::ParserException(const wstring& message)
		: COBJException(message)
	{
	}

	ParserException::ParserException(const wstring& message, const wstring& cause)
		: COBJException(message, cause)
	{
	}

#ifdef _WIN32
	ParserException::ParserException(const wstring& message, errno_t err)
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