#include <Satoshi/stpch.hpp>
#include "Shader.hpp"

#include <Satoshi/Renderer/APIController.hpp>

#include <Satoshi/Platform/Renderer/GL4/GL4Shader.hpp>
#include <Satoshi/Platform/Renderer/D3D11/D3D11Shader.hpp>

Satoshi::Shader* Satoshi::Shader::Create(std::string_view vertexShader, std::string_view fragmentShader)
{
	switch (APIController::GetRendererAPI())
	{
		case RendererAPI::None:	ST_CORE_ASSERT(false, "You must choose a valid Graphic API!"); return nullptr;
		case RendererAPI::GL4:	return new GL4Shader(vertexShader.data(), fragmentShader.data());
		#ifdef ST_PLATFORM_WINDOWS
		case RendererAPI::D3D11:	return new D3D11Shader(vertexShader.data(), fragmentShader.data());
		#endif
	}
	return nullptr;
}
