/*\file OpenGLVertexBuffer.h */

#pragma once
#include "rendering/bufferLayout.h"

namespace Engine
{
	class OpenGLVertexBuffer
	{
	public: 
		OpenGLVertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout); //!< constructor sorting out vertices, size and setting up Buffer layout 
		~OpenGLVertexBuffer(); //!< Default Deconstructor 
		void edit(void* vertices, uint32_t size, uint32_t offset); //!< Function editing the data afterwards  
		inline uint32_t getrenderID() const { return m_OpenGL_ID; }
		inline const VertexBufferLayout& getLayout() const { return m_layout;}
	private:
		uint32_t m_OpenGL_ID; //!< Render ID 
		VertexBufferLayout m_layout;


	};
}
