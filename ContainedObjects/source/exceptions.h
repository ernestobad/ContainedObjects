#pragma once

namespace COBJ
{

	// COBJException //

	class COBJException : public std::exception
	{
	public:
		COBJException(const std::wstring& message);
		COBJException(const std::wstring& message, const std::wstring& cause);
#ifdef _WIN32
		COBJException(const std::wstring& message, errno_t err);
		COBJException(const std::wstring& message, DWORD lastError);
#endif
		COBJException(const COBJException& e);
		virtual ~COBJException(void);

		virtual const std::wstring& getMessage() const;
		virtual const std::wstring& getCause() const;
	private:
		std::wstring m_Message;
		std::wstring m_Cause;
	};

	// InternalErrorException //

	class InternalErrorException : public COBJException
	{
	public:
		InternalErrorException(const std::wstring& message);
		InternalErrorException(const std::wstring& message, const std::wstring& cause);
		InternalErrorException(const InternalErrorException& e);
		virtual ~InternalErrorException(void);
	};

	// IndexOutOfBoundsException //

	class IndexOutOfBoundsException : public COBJException
	{
	public:
		IndexOutOfBoundsException(const std::wstring& message);
		IndexOutOfBoundsException(const std::wstring& message, const std::wstring& cause);
		IndexOutOfBoundsException(const IndexOutOfBoundsException& e);
		virtual ~IndexOutOfBoundsException(void);
	};

	// InvalidTypeException //

	class InvalidTypeException : public COBJException
	{
	public:
		InvalidTypeException(const std::wstring& message);
		InvalidTypeException(const std::wstring& message, const std::wstring& cause);
		InvalidTypeException(const InvalidTypeException& e);
		virtual ~InvalidTypeException(void);
	};

	// IOException //

	class IOException : public COBJException
	{
	public:
		IOException(const std::wstring& message);
		IOException(const std::wstring& message, const std::wstring& cause);
#ifdef _WIN32
		IOException(const std::wstring& message, errno_t err);
#endif
		IOException(const IOException& e);
		virtual ~IOException(void);
	};

	// ParserException //

	class ParserException : public COBJException
	{
	public:
		ParserException(const std::wstring& message);
		ParserException(const std::wstring& message, const std::wstring& cause);
#ifdef _WIN32
		ParserException(const std::wstring& message, errno_t err);
#endif
		ParserException(const ParserException& e);
		virtual ~ParserException(void);
	};

}
 
