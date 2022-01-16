///*\file OpenGLUniformBuffer.h*/
//
//#pragma once
//
//#include "rendering/uniformBuffer.h"
//
//namespace Engine
//{
//	class OpenGLUniformBuffer : public UniformBuffer
//	{
//	public:
//		OpenGLUniformBuffer(const UniformBufferLayout& layout); //!< constructor 
//		~OpenGLUniformBuffer() override;
//		inline uint32_t getID() override { return m_OpenGL_ID; }
//		inline UniformBufferLayout getLayout() override { return m_layout; }
//		void attachShaderBlock(const std::shared_ptr<Shader>& shader, const char* blockName) override;
//		void uploadData(const char* uniformName, void* data) override;
//
//	private:
//		uint32_t m_OpenGL_ID; //!< OpenGL ID
//		static uint32_t s_blockNumber; //!< Global block number
//
//
//	};
//}