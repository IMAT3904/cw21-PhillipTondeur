/**\ file GLFWWindowImpl.h*/
#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>
namespace Engine
{
	/**\class GLFWWindowImpl
	* Implementation of a window using GLFW
	*/
	class GLFWWindowImpl : public Window
	{
	public:
		GLFWWindowImpl(const WindowProperties& properties); //!< Constructor
		virtual void init(const WindowProperties& properties) override; //!< initialises the windows 
		virtual void close() override; //!< closes the window
		//virtual ~Window() {}; //!< virtualises destructor 
		virtual void onUpdate(float timestep) override;
		virtual void setVSync(bool VSync) override; //!< sticks to your refresh rate 
		virtual inline unsigned int getWidth() const override {return m_props.width; }
		virtual inline unsigned int getHeight() const override {return m_props.height; }
		virtual inline void* getNativeWindow() const override {return m_native;} //!< gets the underlying platform 
		virtual inline bool isFullScreenMode() const override {return m_props.isFullScreen;}//!< is it fullscreen?
		virtual inline bool isVSync() const override { return m_props.isVsync;}


	private:
		WindowProperties m_props; //!< Properties 
		GLFWwindow* m_native; //!< Native GLFW window
		float m_aspectRatio; //!< Aspect ratio 

	};
}
