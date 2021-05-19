#ifndef STRING_SERIALIZER_HPP
#define STRING_SERIALIZER_HPP

#include <Satoshi/stpch.hpp>

namespace Satoshi
{
	class StringSerializer
	{
	public:
		static std::string SerializeString(std::string_view arg);
		static std::string DeserializeString(std::string_view arg);
	private:
		static void HexString(char conversor[3], uint8_t number);
		static uint8_t HexASCIICode(uint8_t number);
	};
}

#endif
