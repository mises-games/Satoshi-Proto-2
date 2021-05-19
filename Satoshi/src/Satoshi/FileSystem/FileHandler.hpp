#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <string>
#include <mutex>

namespace Satoshi
{
	class FileHandler
	{
	public:
		static bool Load(const std::string& filepath, std::string* content);
		static bool Store(const std::string& filepath, std::string_view content);
	};
}

#endif
