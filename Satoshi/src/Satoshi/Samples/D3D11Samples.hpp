#ifndef D3D11_SAMPLES_HPP
#define D3D11_SAMPLES_HPP

#include <d3d11.h>
#include <DirectXMath.h>
#include <Satoshi/Platform/Renderer/D3D11/D3D11Context.hpp>
#include "Sample.hpp"
#include <d3dcompiler.h>
#include <Satoshi/Core/Application.hpp>
#include <Satoshi/Renderer/Shader.hpp>
#include <Satoshi/Platform/Renderer/D3D11/D3D11Shader.hpp>

namespace Satoshi
{
	class D3D11Sample1 : public Sample
	{
	public:
		virtual void Start(void* data) override
		{
			HRESULT hr;
			auto contextResource = *static_cast<D3D11ContextData*>(Satoshi::Application::GetInstance()->
				GetWindow()->GetContext()->GetNativeContextData());
			m_Device = contextResource.Device;
			m_DeviceContext = contextResource.DeviceContext;

			std::string vertexShader = "float4 main( float3 pos : POSITION ) : SV_POSITION"
			"{"
			"return float4(pos.x, pos.y, pos.z, 1.0f);"
			"}";
			
			std::string pixelShader = "float4 main( ) : SV_TARGET"
			"{"
			"return float4(1.0f, 1.0f, 1.0f, 1.0f);"
			"}";

			
			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = Satoshi::Application::GetInstance()->
				GetWindow()->GetWidth();
			viewport.Height = Satoshi::Application::GetInstance()->
				GetWindow()->GetHeight();
			viewport.MaxDepth = 1.0f;

			m_DeviceContext->RSSetViewports(1, &viewport);
			
			m_Shader = Shader::Create(vertexShader, pixelShader);

			D3D11_INPUT_ELEMENT_DESC ied[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
			};

			auto d3dShader = static_cast<D3D11Shader*>(m_Shader);

			//temp
			VertexData vertexShaderInstance = d3dShader->GetNativeVertexShader();
			//temp sai com o vertex buffer
			hr = m_Device->CreateInputLayout(ied, 1, vertexShaderInstance.VertexBlob->GetBufferPointer(), vertexShaderInstance.VertexBlob->GetBufferSize(), &m_InputLayout);
			m_DeviceContext->IASetInputLayout(m_InputLayout);


			// create the vertex buffer
			D3D11_BUFFER_DESC bd;
			D3D11_SUBRESOURCE_DATA InitData;
			ZeroMemory(&bd, sizeof(bd));
			ZeroMemory(&InitData, sizeof(InitData));

			bd.Usage = D3D11_USAGE_DEFAULT;                // write access access by CPU and GPU
			bd.ByteWidth = sizeof(vertices);             // size is the VERTEX struct * 3
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
			bd.CPUAccessFlags = 0;    // allow CPU to write in buffer

			InitData.pSysMem = vertices;
			InitData.SysMemPitch = 0;
			InitData.SysMemSlicePitch = 0;

			hr = m_Device->CreateBuffer(&bd, &InitData, &m_VertexBuffer);       // create the buffer

			ZeroMemory(&bd, sizeof(bd));
			ZeroMemory(&InitData, sizeof(InitData));

			bd.Usage = D3D11_USAGE_DEFAULT;                // write access access by CPU and GPU
			bd.ByteWidth = sizeof(indices);             // size is the VERTEX struct * 3
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;       // use as a vertex buffer
			bd.CPUAccessFlags = 0;    // allow CPU to write in buffer

			
			InitData.pSysMem = indices;
			InitData.SysMemPitch = 0;
			InitData.SysMemSlicePitch = 0;

			hr = m_Device->CreateBuffer(&bd, &InitData, &m_IndexBuffer);

		}
		
		virtual void Update() override
		{
			auto contextResource = *static_cast<D3D11ContextData*>(Satoshi::Application::GetInstance()->
				GetWindow()->GetContext()->GetNativeContextData());
			m_Device = contextResource.Device;
			m_DeviceContext = contextResource.DeviceContext;
			// select which vertex buffer to display
			m_Shader->Bind();
			UINT stride = sizeof(float) * 3;
			UINT offset = 0;
			m_DeviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
			m_DeviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			// select which primtive type we are using
			m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// draw the vertex buffer to the back buffer
			m_DeviceContext->DrawIndexed(3,0,0);
		}
	private:
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;
		float vertices[3 * 3] =
		{
			0.0f, 0.5f, 0.0f,
			0.5f, -0.5, 0.0f,
			-0.5f, -0.5f, 0.0f
		};
		uint32_t indices[3] = { 0,1,2 };

		ID3D11Buffer* m_VertexBuffer = nullptr;
		ID3D11Buffer* m_IndexBuffer = nullptr;
		ID3D11InputLayout* m_InputLayout;

		D3D11_VIEWPORT vp = { 0 };
		
		Shader* m_Shader;
	
	};
}

#endif
