/* \ file OpenGLVertexArray.h */

#pragma once

#include <vector>
#include<memory>

#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "rendering/vertexArray.h"


namespace Engine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
		inline uint32_t getID() const override{ return m_OpenGL_ID; }
		inline uint32_t getDrawCount() const override{if (m_indexBuffer) { m_indexBuffer->getCount(); }	else { return 0; }	}
		inline uint32_t getIBOID() const override { if (m_indexBuffer) { return m_indexBuffer->getID(); } else { return -1; } }
	private:
		uint32_t m_OpenGL_ID; 
		uint32_t m_attributeIndex = 0; //!< Attribute Index
	/*	std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;*/

	};
}
