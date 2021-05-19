#ifndef STRING_LOCALER_HPP
#define STRING_LOCALER_HPP

#include <Satoshi/stpch.hpp>

namespace Satoshi
{
	class StringLocaler
	{
	public:
		static std::u32string Utf8ToUtf32(std::string_view arg);
		static std::string Utf32ToUtf8(std::basic_string_view<char32_t> arg);
	private:
		static uint32_t EncodeUTF8(uint32_t charValue);
		static uint32_t DecodeUTF8(uint32_t utfValue);
		static uint32_t DumpU32(char32_t val);
		static char32_t RecoverU32(uint32_t val);
	};
}

#endif
