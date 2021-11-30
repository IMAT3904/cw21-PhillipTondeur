/*\file subTexture.h*/
#pragma once
#include "platform/OpenGL/OpenGLTexture.h"
#include <memory>
#include <glm/glm.hpp>

namespace Engine
{
	class SubTexture
	{
	public:
		SubTexture() {}; //!< Basic constructor 
		SubTexture(const std::shared_ptr<OpenGLTexture>& texture, const glm::vec2& UVStart, const glm::vec2& UVEnd); //!< specialised constructor that needs a texture and Tells the texture what UV bounds we're interested in 
		inline glm::vec2 getUVStart() { return m_UVStart; }
		inline glm::vec2 getUVEnd() { return m_UVEnd; }
		glm::ivec2 getSize() { return m_size; } //!< stored as integers 
		glm::vec2 getSizef() { return { static_cast<float> (m_size.x), static_cast<float>(m_size.y) }; } //!< when we need maths on the size this float point version helps 
		inline uint32_t getWidth() { return m_size.x; } //!< accessor of width
		inline uint32_t getHeight() { return m_size.y; } //!< accessor of height 
		inline uint32_t getWidthf() { return static_cast<float>(m_size.x); } //!< accessor of widthf
		inline uint32_t getHeightf() { return static_cast<float>(m_size.y); } //!< accessor of heightf
		float transformU(float U); //!< transform original to co-ord in the atlas
		float transformV(float V); //!< transform original to co-ord in the atlas 
		glm::vec2 transformUV(glm::vec2 UV);
	private:
		std::shared_ptr<OpenGLTexture> m_texture; //!< stores texture
		glm::vec2 m_UVStart; //!< stores start of the UV bounds
		glm::vec2 m_UVEnd; //!< stores end of the uv bounds 
		glm::ivec2 m_size; //!< Size in pixels 
	};
}