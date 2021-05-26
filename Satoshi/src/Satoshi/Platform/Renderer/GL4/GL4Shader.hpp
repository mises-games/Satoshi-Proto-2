#ifndef GL4_SHADER_HPP
#define GL4_SHADER_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Renderer/Shader.hpp>
#include "gl_safe_include.h"

namespace Satoshi
{
	struct GL4ShaderInitializer
	{
		unsigned Type;
		std::string Shader;
	};

	class GL4Shader : public Shader 
	{
	public:
		GL4Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~GL4Shader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t CompileShader(std::string_view shaderSource, GLenum shaderType);
		uint32_t CreateShader(std::vector<GL4ShaderInitializer> shaderSource);

		uint32_t m_RendererID;
	};
}

#endif
