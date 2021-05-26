#ifndef WIN32_MAPPER_CODES_HPP
#define WIN32_MAPPER_CODES_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Core/InputCodes.hpp>

namespace Satoshi
{
	class Win32InputMapper
	{
	public:
		static uint16_t MapInput(uint16_t code)
		{
			uint16_t key = 0;
			if (s_Codes.find(code) != s_Codes.end())
				key = s_Codes[code];
			return key;
		}
	private:
		static std::unordered_map<uint16_t, uint16_t> s_Codes;
	};
}

#endif
