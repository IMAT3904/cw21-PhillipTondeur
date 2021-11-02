/*\file inputPoller.h*/

#pragma once
#include<glm/glm.hpp>

namespace Engine
{
	/* \ class InputPoller 
	*	API agnoistic input poller for getting current keyboard nad mouse state
	*/
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< is the key pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< is the mouse button pressed
		static glm::vec2 getMousePostion(); //!< current mouse position 
		static void setNativeWindow(void* nativeWin);
		inline static float getMouseX() { return getMousePostion().x; }
		inline static float getMouseY() { return getMousePostion().y; }
	};
}
