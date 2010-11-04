
#pragma once

#ifdef _WIN32

namespace COBJ
{
	void convertUTF16ToUTF8(const std::wstring& utf16_str, std::string& utf8_str);

	void convertUTF8ToUTF16(const std::string& utf8_str, std::wstring& utf16_str);
}

#endif