/*\file OpenGLUniformBuffer.h*/

#pragma once
#include "rendering/bufferLayout.h"
#include <unordered_map>
#include "platform/OpenGL/OpenGLShader.h"
#include <memory>
namespace Engine
{
	class OpenGLUniformBuffer
	{
	public:
		OpenGLUniformBuffer(const UniformBufferLayout& layout); //!< constructor 
		OpenGLUniformBuffer();
		inline uint32_t getRenderID() { return m_OpenGL_ID; }
		inline UniformBufferLayout getLayout() { return m_layout; }
		void attachShaderBlock(const std::shared_ptr<OpenGLShader>& shader, const char* blockName);
		void uploadData(const char* uniformName, void* data);

	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID
		UniformBufferLayout m_layout; //!< Uniform Buffer layout 
		std::unordered_map<const char*, std::pair<uint32_t, uint32_t>> m_uniformCache; //!< Stores uniform names with offsets and sizes
		uint32_t m_blockNumber; //!< Block number for this UBO
		static uint32_t s_blockNumber; //!< Global block number


	};
}