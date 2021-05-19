#include <Satoshi/stpch.hpp>
#include "FileHandler.hpp"

bool Satoshi::FileHandler::Load(const std::string& filepath, std::string* content)
{
	bool loaded = false;
	std::ifstream fileStream;
	try
	{
		fileStream.open(filepath, std::ios::binary);
		loaded = true;
	}
	catch (...)
	{
		return loaded;
	}
	auto start = fileStream.tellg();
	fileStream.seekg(0, std::ios::end);
	uint64_t fsize = fileStream.tellg() - start;
	fileStream.seekg(0, std::ios::beg);
	char* buffer = new char[fsize + 1];
	buffer[fsize] = '\0';
	fileStream.read(buffer, fsize);
	*content = buffer;
	delete[] buffer;
	return loaded;
}

bool Satoshi::FileHandler::Store(const std::string& filepath, std::string_view content)
{
	bool stored = false;
	std::ofstream fileStream;
	try
	{
		fileStream.open(filepath, std::ios::binary);
		stored = true;
	}
	catch (...)
	{
		return stored;
	}
	fileStream << content;
	return stored;
}
