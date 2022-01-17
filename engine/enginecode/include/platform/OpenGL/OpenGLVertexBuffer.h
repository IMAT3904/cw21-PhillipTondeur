/*\file OpenGLVertexBuffer.h */

#pragma once
#include "rendering/bufferLayout.h"
#include "rendering/vertexBuffer.h"

namespace Engine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout layout);
		~OpenGLVertexBuffer();
		inline void edit(void* vertices, uint32_t size, int32_t offset);
		inline uint32_t getID() const  { return m_OpenGL_ID; }
		inline const BufferLayout& getLayout() const  { return m_layout; }

	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID
		BufferLayout m_layout;
	};
}
