#include <Satoshi/stpch.hpp>
#include "D3D11Shader.hpp"

#include <Satoshi/Core/Application.hpp>
#include "D3D11Context.hpp"

Satoshi::D3D11Shader::D3D11Shader(const std::string& vertexSource, const std::string& pixelSource)
{
	CreateShader({ vertexSource, "vs_4_0", "main" }, { pixelSource, "ps_4_0", "main" });
}

Satoshi::D3D11Shader::~D3D11Shader()
{
}

void Satoshi::D3D11Shader::Bind() const
{
	auto contextResource = *static_cast<D3D11ContextData*>(Satoshi::Application::GetInstance()->
		GetWindow()->GetContext()->GetNativeContextData());
	
	contextResource.DeviceContext->VSSetShader(m_VertexData.VertexShader, NULL, 0);
	contextResource.DeviceContext->PSSetShader(m_PixelData.PixelShader, NULL, 0);

	//contextResource.DeviceContext->VSSetConstantBuffers(0, m_VSConstantBuffersCount, m_VSConstantBuffers);
	//contextResource.DeviceContext->PSSetConstantBuffers(0, m_PSConstantBuffersCount, m_PSConstantBuffers);
}

void Satoshi::D3D11Shader::Unbind() const
{
}

ID3DBlob* Satoshi::D3D11Shader::CompileShader(std::string_view shaderSource, std::string_view shaderType, std::string_view main)
{
	ID3DBlob* shaderBlob;
	ID3DBlob* errorBlob;
	HRESULT status = D3DCompile(shaderSource.data(), shaderSource.size(), NULL, NULL, NULL, main.data(), shaderType.data(), D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);
	if (errorBlob)
	{
		if (errorBlob->GetBufferSize())
			ST_CORE_ASSERT(!errorBlob, "Shader Compile Errors: {0}", (const char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}
	if (status == S_OK)
		return shaderBlob;
	return NULL;
}

void Satoshi::D3D11Shader::CreateShader(D3D11ShaderInitializer vertexSource, D3D11ShaderInitializer pixelSource)
{
	m_VertexData.VertexBlob = CompileShader(vertexSource.Shader, vertexSource.Type, vertexSource.Main);
	m_PixelData.PixelBlob = CompileShader(pixelSource.Shader, pixelSource.Type, pixelSource.Main);

	auto contextResource = *static_cast<D3D11ContextData*>(Satoshi::Application::GetInstance()->
		GetWindow()->GetContext()->GetNativeContextData());
	
	contextResource.Device->CreateVertexShader(m_VertexData.VertexBlob->GetBufferPointer(), m_VertexData.VertexBlob->GetBufferSize(), nullptr, &m_VertexData.VertexShader);
	contextResource.Device->CreatePixelShader(m_PixelData.PixelBlob->GetBufferPointer(), m_PixelData.PixelBlob->GetBufferSize(), nullptr, &m_PixelData.PixelShader);
}
