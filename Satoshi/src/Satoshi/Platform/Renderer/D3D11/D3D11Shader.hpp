#ifndef D3D11_SHADER_HPP
#define D3D11_SHADER_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Renderer/Shader.hpp>
#include <d3d11.h>
#include <d3dcompiler.h>

namespace Satoshi
{
	struct D3D11ShaderInitializer
	{
		std::string Shader;
		std::string Type;
		std::string Main;
	};

	struct VertexData
	{
		ID3D11VertexShader* VertexShader;
		ID3DBlob* VertexBlob;
	};
	
	struct PixelData
	{
		ID3D11PixelShader* PixelShader;
		ID3DBlob* PixelBlob;
	};
	
	struct GeometryData
	{
		ID3D11GeometryShader* GeometryShader;
		ID3DBlob* GeometryBlob;
	};

	class D3D11Shader : public Shader
	{
		friend class D3D11Sample1;
	public:
		D3D11Shader(const std::string& vertexSource, const std::string& pixelSource);
		~D3D11Shader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		
	private:
		virtual VertexData GetNativeVertexShader() { return m_VertexData; }

		ID3DBlob* CompileShader(std::string_view shaderSource, std::string_view shaderType, std::string_view main);
		void CreateShader(D3D11ShaderInitializer vertexSource, D3D11ShaderInitializer pixelSource);

		VertexData m_VertexData;
		PixelData m_PixelData;
		//GeometryData m_GeometryData;
	};
}

#endif
