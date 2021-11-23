/**\file window.h */

#pragma once

#include "events/eventHandler.h"
#include "core/graphicsContext.h"

namespace Engine
{
	/**\ class Window 
	* Abstract windows base class. All Implimented windows should code to this Interface.
	*/

	struct WindowProperties
	{
		char* title;
		uint32_t width;
		uint32_t height;
		bool isFullScreen;
		bool isVsync;

		WindowProperties(char * title = "My Window", uint32_t width = 800, uint32_t height = 600, bool fullscreen = false) : title(title), width(width), height(height), isFullScreen(fullscreen) {}
	};

	class Window
	{
	public:
		virtual void init(const WindowProperties& properties) = 0; //!< initialises the windows 
		virtual void close() = 0; //!< closes the window
		virtual ~Window() {}; //!< virtualises destructor 
		virtual void onUpdate(float timestep) = 0;
		virtual void setVSync(bool VSync) = 0; //!< sticks to your refresh rate 
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual void* getNativeWindow() const = 0; //!< gets the underlying platform 
		virtual bool isFullScreenMode() const = 0; //!< is it fullscreen?
		virtual bool isVSync() const = 0;

		inline EventHandler& getEventHandler() { return m_handler; }

		static Window* create(const WindowProperties& properties = WindowProperties());
	protected:
		EventHandler m_handler; //!< Event handler
		std::shared_ptr<GraphicsContext> m_graphicsContext;
	};
}
