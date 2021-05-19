#ifndef STRING_ASSERTION_HPP
#define STRING_ASSERTION_HPP

#include <Satoshi/stpch.hpp>

namespace Satoshi
{
	class TypeAssertion
	{
	public:
		template <typename T, typename S>
		inline static bool AssertTypeIDs();
		template<typename T>
		inline static bool IsValidString();
		template<typename T>
		inline static bool IsValidChar();
		template<typename T>
		inline static bool IsValidInt();
		template<typename String, typename Primitive>
		inline static bool IsValidPrimitive();
	};

}

template<typename T, typename S>
inline bool Satoshi::TypeAssertion::AssertTypeIDs()
{
	return typeid(T) == typeid(S);
}

template<typename T>
inline bool Satoshi::TypeAssertion::IsValidString()
{
	bool isValidString = false;

	isValidString = isValidString || AssertTypeIDs<std::string, T>();
	isValidString = isValidString || AssertTypeIDs<std::u16string, T>();
	isValidString = isValidString || AssertTypeIDs<std::u32string, T>();
	isValidString = isValidString || AssertTypeIDs<std::wstring, T>();

	return isValidString;
}

template<typename T>
inline bool Satoshi::TypeAssertion::IsValidChar()
{
	bool isValidChar = false;

	isValidChar = isValidChar || AssertTypeIDs<char, T>();
	isValidChar = isValidChar || AssertTypeIDs<char16_t, T>();
	isValidChar = isValidChar || AssertTypeIDs<char32_t, T>();
	isValidChar = isValidChar || AssertTypeIDs<wchar_t, T>();

	return isValidChar;
}

template<typename T>
inline bool Satoshi::TypeAssertion::IsValidInt()
{
	bool isValidInt = false;

	isValidInt = isValidInt || AssertTypeIDs<int8_t, T>();
	isValidInt = isValidInt || AssertTypeIDs<int16_t, T>();
	isValidInt = isValidInt || AssertTypeIDs<int32_t, T>();
	isValidInt = isValidInt || AssertTypeIDs<int64_t, T>();
	isValidInt = isValidInt || AssertTypeIDs<uint8_t, T>();
	isValidInt = isValidInt || AssertTypeIDs<uint16_t, T>();
	isValidInt = isValidInt || AssertTypeIDs<uint32_t, T>();
	isValidInt = isValidInt || AssertTypeIDs<uint64_t, T>();

	return isValidInt;
}

template<typename String, typename Primitive>
inline bool Satoshi::TypeAssertion::IsValidPrimitive()
{
	std::bitset<4> validStringTypes;

	validStringTypes[0] = AssertTypeIDs<String, std::string>();
	validStringTypes[1] = AssertTypeIDs<String, std::u16string>();
	validStringTypes[2] = AssertTypeIDs<String, std::u32string>();
	validStringTypes[3] = AssertTypeIDs<String, std::wstring>();

	uint64_t validStringMappedBits = validStringTypes.to_ullong();

	switch (validStringMappedBits)
	{
	case 1:
		return Satoshi::TypeAssertion::AssertTypeIDs<char, Primitive>();
	case 2:
		return Satoshi::TypeAssertion::AssertTypeIDs<char16_t, Primitive>();
	case 4:
		return Satoshi::TypeAssertion::AssertTypeIDs<char32_t, Primitive>();
	case 8:
		return Satoshi::TypeAssertion::AssertTypeIDs<wchar_t, Primitive>();
	}
	return false;
}

#endif
