/* \file renderAPI.cpp*/


#include "engine_pch.h"
#include "rendering/RenderAPI.h"
#include "rendering/IndexBuffer.h"
#include "platform/OpenGL/OpenGLIndexBuffer.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"
#include "systems/log.h"

namespace Engine 
{
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None :
			Log::error("No Rendering API is not supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not supported");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan is not supported");
			break;
		}
		return nullptr;
	}
	
	UniformBuffer* UniformBuffer::create(const UniformBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No Rendering API is not supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLUniformBuffer(layout);
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not supported");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan is not supported");
			break;
		}
		return nullptr;
	}

}