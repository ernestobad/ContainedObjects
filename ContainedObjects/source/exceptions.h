#pragma once

namespace COBJ
{
	using namespace std;

	// COBJException //

	class COBJException : public exception
	{
	public:
		COBJException(const wstring& message);
		COBJException(const wstring& message, const wstring& cause);
#ifdef _WIN32
		COBJException(const wstring& message, errno_t err);
		COBJException(const wstring& message, DWORD lastError);
#endif
		COBJException(const COBJException& e);
		virtual ~COBJException(void);

		void printStackTrace(wostream& out) const;

		virtual const wstring& getMessage() const;
		virtual const wstring& getCause() const;

	private:

		void fillStackTrace();

		list<wstring> m_StackTrace;
		wstring m_Message;
		wstring m_Cause;
	};

	// InternalErrorException //

	class InternalErrorException : public COBJException
	{
	public:
		InternalErrorException(const wstring& message);
		InternalErrorException(const wstring& message, const wstring& cause);
		InternalErrorException(const InternalErrorException& e);
		virtual ~InternalErrorException(void);
	};

	// RuntimeCheckException //

	class RuntimeCheckException : public COBJException
	{
	public:
		RuntimeCheckException(const wstring& message);
		RuntimeCheckException(const wstring& message, const wstring& cause);
		RuntimeCheckException(const RuntimeCheckException& e);
		virtual ~RuntimeCheckException(void);
	};

	// IndexOutOfBoundsException //

	class IndexOutOfBoundsException : public COBJException
	{
	public:
		IndexOutOfBoundsException(const wstring& message);
		IndexOutOfBoundsException(const wstring& message, const wstring& cause);
		IndexOutOfBoundsException(const IndexOutOfBoundsException& e);
		virtual ~IndexOutOfBoundsException(void);
	};

	// InvalidTypeException //

	class InvalidTypeException : public COBJException
	{
	public:
		InvalidTypeException(const wstring& message);
		InvalidTypeException(const wstring& message, const wstring& cause);
		InvalidTypeException(const InvalidTypeException& e);
		virtual ~InvalidTypeException(void);
	};

	// IOException //

	class IOException : public COBJException
	{
	public:
		IOException(const wstring& message);
		IOException(const wstring& message, const wstring& cause);
#ifdef _WIN32
		IOException(const wstring& message, errno_t err);
#endif
		IOException(const IOException& e);
		virtual ~IOException(void);
	};

	// ParserException //

	class ParserException : public COBJException
	{
	public:
		ParserException(const wstring& message);
		ParserException(const wstring& message, const wstring& cause);
#ifdef _WIN32
		ParserException(const wstring& message, errno_t err);
#endif
		ParserException(const ParserException& e);
		virtual ~ParserException(void);
	};

}
 
