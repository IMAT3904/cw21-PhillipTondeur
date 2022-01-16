/* \file OpenGlShader.h*/

#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include "rendering/shader.h"

namespace Engine 
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath); //!< Constructor that takes const chars from the filepaths of vertex and fragment
		OpenGLShader(const char* filepath); //!< Constructor that takes one single file 
		~OpenGLShader(); //!< default destructor 
		uint32_t getID() const { return m_OpenGL_ID; } //!< Accessor 

		void uploadInt(const char* name, int value); //!< Allows us to upload Ints 
		void uploadFloat(const char* name, float value); //!< Allows us to upload the first float  
		void uploadFloat2(const char* name, const glm::vec2& value); //!< the Second 
		void uploadFloat3(const char* name, const glm::vec3& value); //!< the third float
		void uploadFloat4(const char* name, const glm::vec4& value); //!< the fourth float 
		void uploadMat4(const char* name, const glm::mat4& value); //!< Helps us upload the matrices 
	private:
		uint32_t m_OpenGL_ID;
		void compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc); //!< only doing Vertex and Fragment Shaders since we're only dealing with them
	};
}
