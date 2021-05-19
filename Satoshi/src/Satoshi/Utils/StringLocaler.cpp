#include <Satoshi/stpch.hpp>
#include "StringLocaler.hpp"

std::u32string Satoshi::StringLocaler::Utf8ToUtf32(std::string_view arg)
{
	std::u32string convertedString;
	char32_t* buffer = new char32_t[(arg.size()) + 1];
	for (size_t i = 0; i < arg.size(); i++)
	{
		buffer[i] = U'\0';
	}
	for (size_t i = 0, j = 0; i < arg.size(); ++i, j++)
	{
		uint32_t code = 0;
		unsigned char element = arg.at(i);
		if (((uint32_t)element >> 7) == 0)
		{
			code = (uint32_t)element;
		}
		if (((uint32_t)element >> 5) == 6)
		{
			code = ((uint32_t)(element) << 8);
			i++;
			element = arg.at(i);
			code += (uint32_t)(element);
		}
		if (((uint32_t)element >> 4) == 14)
		{
			code = ((uint32_t)(element) << 16);
			i++;
			element = arg.at(i);
			code += ((uint32_t)(element) << 8);
			i++;
			element = arg.at(i);
			code += ((uint32_t)(element));
		}
		if (((uint32_t)element >> 3) == 30)
		{
			code = ((uint32_t)(element) << 24);
			i++;
			element = arg.at(i);
			code += ((uint32_t)(element) << 16);
			i++;
			element = arg.at(i);
			code += ((uint32_t)(element) << 8);
			i++;
			element = arg.at(i);
			code += ((uint32_t)(element));
		}
		buffer[j] = RecoverU32(DecodeUTF8(code));
	}
	if (arg.size() > 0)
		convertedString = buffer;
	else
		convertedString = U"";
	delete[] buffer;
	return convertedString;
}

std::string Satoshi::StringLocaler::Utf32ToUtf8(std::basic_string_view<char32_t> arg)
{
	char* buffer = new char[(arg.size() * 4) + 1];
	for (size_t i = 0; i <= (arg.size() * 4); i++)
	{
		buffer[i] = '\0';
	}
	std::string convertedString;
	char charList[4] = {'\0','\0','\0','\0'};
	for (size_t i = 0, j = 0; i < arg.size(); i++)
	{
		uint32_t uniCode = EncodeUTF8(DumpU32(arg.at(i)));
		size_t k;
		for (k = 0; uniCode > 0; k++)
		{
			charList[k] = (char)((uniCode) % BIT(8));
			uniCode >>= 8;
		}
		for (size_t l = k; l > 0; j++, l--)
		{
			buffer[j] = charList[l - 1];
		}
	}
	if (arg.size() > 0)
		convertedString = buffer;
	else
		convertedString = "";
	delete[] buffer;
	return convertedString;
}

uint32_t Satoshi::StringLocaler::EncodeUTF8(uint32_t charValue)
{
	uint32_t utf8char = 0;
	if (charValue < BIT(7))
	{
		return charValue;
	}
	if (charValue < BIT(11))
	{
		utf8char |= (BIT(7) | (charValue % BIT(6)));
		charValue >>= 6;
		utf8char |= (BIT(15) | BIT(14) | (charValue << 8));
		return utf8char;
	}
	if (charValue < BIT(16))
	{
		utf8char |= (BIT(7) | (charValue % BIT(6)));
		charValue >>= 6;
		utf8char |= (BIT(15) | ((charValue % BIT(6)) << 8));
		charValue >>= 6;
		utf8char |= (BIT(23) | BIT(22) | BIT(21) | (charValue << 16));
		return utf8char;
	}
	if (charValue < BIT(21))
	{
		utf8char |= (BIT(7) | (charValue % BIT(6)));
		charValue >>= 6;
		utf8char |= (BIT(15) | ((charValue % BIT(6)) << 8));
		charValue >>= 6;
		utf8char |= (BIT(23) | ((charValue % BIT(6)) << 16));
		charValue >>= 6;
		utf8char |= (BIT(31) | BIT(30) | BIT(29) | BIT(28) | (charValue << 24));
		return utf8char;
	}
	return utf8char;
}

uint32_t Satoshi::StringLocaler::DecodeUTF8(uint32_t utfValue)
{
	uint32_t charValue = 0;
	if (utfValue < BIT(8))
	{
		return utfValue;
	}
	if (utfValue < BIT(16))
	{
		charValue += (utfValue % BIT(6));
		utfValue >>= 8;
		charValue += ((utfValue % BIT(5)) << 6);
		return charValue;
	}
	if (utfValue < BIT(24))
	{
		charValue += (utfValue % BIT(6));
		utfValue >>= 8;
		charValue += ((utfValue % BIT(6)) << 6);
		utfValue >>= 8;
		charValue += ((utfValue % BIT(4)) << 12);
		return charValue;
	}
	else
	{
		charValue += (utfValue % BIT(6));
		utfValue >>= 8;
		charValue += ((utfValue % BIT(6)) << 6);
		utfValue >>= 8;
		charValue += ((utfValue % BIT(6)) << 12);
		utfValue >>= 8;
		charValue += ((utfValue % BIT(3)) << 18);
		return charValue;
	}
}

uint32_t Satoshi::StringLocaler::DumpU32(char32_t val)
{
	const uint32_t* data = reinterpret_cast<uint32_t*>(&val);
	return *data;
}

char32_t Satoshi::StringLocaler::RecoverU32(uint32_t val)
{
	const char32_t* data = reinterpret_cast<char32_t*>(&val);
	return *data;
}
