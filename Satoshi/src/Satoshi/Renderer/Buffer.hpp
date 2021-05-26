#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <Satoshi/stpch.hpp>

namespace Satoshi
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Uint,
		Uint2,
		Uint3,
		Uint4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Uint: return 4;
		case ShaderDataType::Uint2: return 4 * 2;
		case ShaderDataType::Uint3: return 4 * 3;
		case ShaderDataType::Uint4: return 4 * 4;
		case ShaderDataType::Bool: return 1;
		}

		ST_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		uint32_t Offset;
		uint32_t Size;
		ShaderDataType Type;

		BufferElement(const std::string& name, ShaderDataType type)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0)
		{}
	};
	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}
		
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	private:
		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
		
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(const void* data, size_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};
}

#endif
