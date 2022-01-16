/*\file OpenGLTexture.h*/

#pragma once

#include <cstdint>
#include "rendering/texture.h"

namespace Engine
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const char* filepath); //!< gets the filepath 
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data); //!< constructor which makes a filepath from data 
		~OpenGLTexture(); //!< default destructor 
		void edit(int32_t xOffset, int32_t yOffset, uint32_t width, uint32_t height, unsigned char* data)override; //!< gives us the ability to edit the texture
		inline uint32_t getID() { return m_OpenGL_ID; } //!< accessor of ID
		inline uint32_t getWidth() { return m_width; } //!< accessor of width
		inline uint32_t getHeight() { return m_height; } //!< accessor of height 
		inline uint32_t getWidthf() { return static_cast<float>(m_width); } //!< accessor of widthf
		inline uint32_t getHeightf() { return static_cast<float>(m_height); } //!< accessor of heightf
		inline uint32_t getChannels() { return m_channels; } //!< accessor of channels 
		void bindToUnit(uint32_t unit) override;

	private:
		uint32_t m_OpenGL_ID; //!< variable of the ID
		uint32_t m_width; //!< variable of width
		uint32_t m_height; //!< variable of height
		uint32_t m_channels; //!< variable of channels 
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data); 
		
	};
}
