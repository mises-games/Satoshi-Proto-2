#ifndef GL4_SAMPLES_HPP
#define GL4_SAMPLES_HPP

#include <Satoshi/Platform/Renderer/GL4/gl_safe_include.h>
#include <glm/glm.hpp>
#include "Sample.hpp"

namespace Satoshi 
{
	class GL4Sample1 : public Sample
	{
	public:
		virtual void Start(void* data) override
		{
			glGenVertexArrays(1, &m_VertexArray);
			glBindVertexArray(m_VertexArray);

			glGenBuffers(1, &m_VertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		
			glGenBuffers(1, &m_IndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		}
		
		virtual void Update() override
		{
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		}
	private:
		float vertices[3 * 3] =
		{
			-.5f, -.5f, .0f,
			.5f, -.5f, .0f,
			.0f, .5f, .0f
		};
		unsigned indices[3] = { 0,1,2 };
		uint32_t m_VertexArray;
		uint32_t m_VertexBuffer;
		uint32_t m_IndexBuffer;
	};
}

#endif
