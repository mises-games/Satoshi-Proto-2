#include <Satoshi/stpch.hpp>
#include "GL4Shader.hpp"

Satoshi::GL4Shader::GL4Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	std::vector<GL4ShaderInitializer> shaders;
	shaders.push_back({ GL_VERTEX_SHADER, vertexSource });
	shaders.push_back({ GL_FRAGMENT_SHADER, fragmentSource });
	m_RendererID = CreateShader(shaders);
}

Satoshi::GL4Shader::~GL4Shader()
{
	glDeleteProgram(m_RendererID);
}

void Satoshi::GL4Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Satoshi::GL4Shader::Unbind() const
{
	glUseProgram(0);
}

uint32_t Satoshi::GL4Shader::CompileShader(std::string_view shaderSource, GLenum shaderType)
{
	uint32_t shader = glCreateShader(shaderType);
	const GLchar* src = shaderSource.data();

	glShaderSource(shader, 1, &src, 0);
	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled != GL_TRUE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

		ST_CORE_ERROR("{0}", infoLog.data());
		ST_CORE_ASSERT(false, "Vertex shader compilation failure!");
		return 0;
	}

	return shader;
}

uint32_t Satoshi::GL4Shader::CreateShader(std::vector<GL4ShaderInitializer> shaderSource)
{
	GLuint program = glCreateProgram();
	std::vector<unsigned> shaders;

	for (auto& shader : shaderSource)
		shaders.push_back(CompileShader(shader.Shader, shader.Type));

	for (auto& shader : shaders)
		glAttachShader(program, shader);
	glLinkProgram(program);

	int isLinked;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

	if (isLinked != GL_TRUE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		ST_CORE_ERROR("{0}", infoLog.data());
		ST_CORE_ASSERT(false, "Vertex shader compilation failure!");
		program = 0;
		for (auto& shader : shaders)
			glDeleteShader(shader);
	}

	for (auto& shader : shaders)
		glDetachShader(program, shader);

	return program;
}
