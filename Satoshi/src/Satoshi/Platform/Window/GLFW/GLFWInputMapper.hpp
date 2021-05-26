#ifndef GLFW_MAPPER_CODES_HPP
#define GLFW_MAPPER_CODES_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Core/InputCodes.hpp>

namespace Satoshi
{
	class GLFWInputMapper
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
