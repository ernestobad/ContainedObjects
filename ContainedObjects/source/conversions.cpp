#include "platform.h"
#include "conversions.h"
#include "exceptions.h"

namespace COBJ
{
	void convertUTF16ToUTF8(const std::wstring& utf16_str, std::string& utf8_str)
	{
#ifdef _WIN32
		int utf8_length = ::WideCharToMultiByte(
			CP_UTF8,
			0,
			utf16_str.data(),
			utf16_str.length(),
			NULL,
			0,
			NULL,
			NULL);

		if (utf8_length == 0)
		{
			DWORD lastError = ::GetLastError();
			std::wstring msg(L"Unable to convert UTF-16 string into UTF-8 string.");
			COBJException e(msg, lastError);
			throw e;
		}

		boost::scoped_array<char> utf8_buff(new char[utf8_length]);

		utf8_length = ::WideCharToMultiByte(
			CP_UTF8,
			0,
			utf16_str.data(),
			utf16_str.length(),
			utf8_buff.get(),
			utf8_length,
			NULL,
			NULL);

		if (utf8_length == 0)
		{
			DWORD lastError = ::GetLastError();
			std::wstring msg(L"Unable to convert UTF-16 string into UTF-8 string.");
			COBJException e(msg, lastError);
			throw e;
		}

		utf8_str = std::string(utf8_buff.get(), utf8_length);
#endif
	}

	void convertUTF8ToUTF16(const std::string& utf8_str, std::wstring& utf16_str)
	{
#ifdef _WIN32

		int utf16_length = ::MultiByteToWideChar(
			CP_UTF8,
			0,
			utf8_str.data(),
			utf8_str.length(),
			NULL,
			0);

		if (utf16_length == 0)
		{
			DWORD lastError = ::GetLastError();
			std::wstring msg(L"Unable to convert UTF-8 string into UTF-16 string.");
			COBJException e(msg, lastError);
			throw e;
		}

		boost::scoped_array<wchar_t> utf16_buff(new wchar_t[utf16_length]);

		utf16_length = ::MultiByteToWideChar(
			CP_UTF8,
			0,
			utf8_str.data(),
			utf8_str.length(),
			utf16_buff.get(),
			utf16_length);

		if (utf16_length == 0)
		{
			DWORD lastError = ::GetLastError();
			std::wstring msg(L"Unable to convert UTF-8 string into UTF-16 string.");
			COBJException e(msg, lastError);
			throw e;
		}

		utf16_str = std::wstring(utf16_buff.get(), utf16_length);
#endif
	}
}

