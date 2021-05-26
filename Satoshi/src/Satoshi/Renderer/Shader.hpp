#ifndef SHADER_HPP
#define SHADER_HPP

namespace Satoshi
{
	class Shader
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(std::string_view vertexShader, std::string_view fragmentShader);
	};
}

#endif
