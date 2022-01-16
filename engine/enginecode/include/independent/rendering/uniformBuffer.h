/**\file uniformBuffer.h */

#pragma once

//#include <ctype.h>
//#include <memory>
//#include <unordered_map>
//
//
//#include "bufferLayout.h"
//#include "platform/OpenGL/OpenGLShader.h"
//#include "shader.h"
//
//
//namespace Engine
//{
//	class UniformBuffer
//	{
//	public:
//	virtual ~UniformBuffer() = default;
//	virtual  uint32_t getID() = 0;
//	virtual  UniformBufferLayout getLayout() = 0;
//	virtual void attachShaderBlock(const std::shared_ptr<Shader>& shader, const char* blockName) = 0;
//	virtual void uploadData(const char* uniformName, void* data) =0;
//
//	static UniformBuffer* create(const UniformBufferLayout& layout);
//
//	protected:
//		
//		UniformBufferLayout m_layout; //!< Uniform Buffer layout 
//		std::unordered_map<const char*, std::pair<uint32_t, uint32_t>> m_uniformCache; //!< Stores uniform names with offsets and sizes
//		uint32_t m_blockNumber; //!< Block number for this UBO
//
//	};
//}
