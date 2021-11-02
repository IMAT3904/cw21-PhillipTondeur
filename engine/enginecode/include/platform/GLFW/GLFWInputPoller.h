
/*\file GLFWInputPoller.h*/

#pragma once
#include<glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{
	/* \ class GLFWInputPoller
	*	API agnoistic input poller for getting current keyboard and mouse state - specific only to GLFW 
	*/
	class GLFWInputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< is the key pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< is the mouse button pressed
		static glm::vec2 getMousePostion(); //!< current mouse position 
		static void setCurrentWindow(GLFWwindow* newWin) { s_window = newWin; } //static Window 
	private:
		static GLFWwindow* s_window; //!< current GLFW window
	};
}
