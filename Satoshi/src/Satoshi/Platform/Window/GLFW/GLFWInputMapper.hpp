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
			return s_Codes[code - 1];
		}
	private:
		static uint16_t s_Codes[116];
	};
}

#endif
