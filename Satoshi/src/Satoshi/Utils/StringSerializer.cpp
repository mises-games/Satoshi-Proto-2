#include <Satoshi/stpch.hpp>
#include "StringSerializer.hpp"

std::string Satoshi::StringSerializer::SerializeString(std::string_view arg)
{
	char* buffer = new char[((arg.size() * 2) + 1)];
	std::string serializedString;
	size_t counter = 0;
	char hex[3];
	for (char c : arg)
	{
		HexString(hex,(uint8_t)c);
		buffer[counter] = hex[0];
		counter++;
		buffer[counter] = hex[1];
		counter++;
	}
	buffer[counter] = '\0';
	if (arg.size() > 0)
		serializedString = buffer;
	else
		serializedString = "";
	delete[] buffer;
	return serializedString;
}

std::string Satoshi::StringSerializer::DeserializeString(std::string_view arg)
{
	char hex[3] = {'\0','\0','\0'};
	char *deserializer = new char[(arg.size()/2) + 1];
	for (size_t i = 0, j = 0; i < arg.length(); ++i, ++j)
	{
		hex[0] = arg.at(i);
		i++;
		hex[1] = arg.at(i);
		unsigned char code = strtol(hex, NULL, 16);
		deserializer[j] = (char)code;
	}
	deserializer[(arg.size() / 2)] = '\0';
	std::string deserializedString;
	if (arg.size() > 0)
		deserializedString = deserializer;
	else
		deserializedString = "";
	delete[] deserializer;
	return deserializedString;
}

void Satoshi::StringSerializer::HexString(char conversor[3], uint8_t number)
{
	conversor[0] = (char)HexASCIICode(number >> 4);
	conversor[1] = (char)HexASCIICode(number % BIT(4));
}

uint8_t Satoshi::StringSerializer::HexASCIICode(uint8_t number)
{
	if (number >= 10)
		return number + 55;
	if (number > 15)
		return 0;
	else
		return number + 48;
}
