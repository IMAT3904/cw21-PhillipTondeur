/* GLFW_OpenGL_GC.h */

#pragma once

#include "include/independent/core/graphicsContext.h"

namespace Engine
{
	class GLFW_OpenGL_GC : public GraphicsContext
	{
	public:
		GLFW_OpenGL_GC(GLFWwindow* win) : m_window(win) {}
		virtual void init() override ; //!< Init the graphics context for the windowing API 
		virtual void swapBuffers() override ; //!< Swapping the buffers 
	private:
		GLFWwindow* m_window; //!< Pointer to GLFW window 
	};
}