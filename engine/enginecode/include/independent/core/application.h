/** \file application.h
*/
#pragma once

#include "systems/log.h"
#include "core/timer.h"
#include "events/events.h"
#include "core/window.h"


namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
		std::shared_ptr<Log> m_logSystem; //!< Log system
		std::shared_ptr<System> m_windowsSystem; //!< Windows System

		std::shared_ptr<Window> m_window; //!< Window
		std::shared_ptr<ChronoTimer> m_timer; //!< Timer
		bool onClose(WindowCloseEvent& e); //!< Run when the window closes
		bool onResize(WindowResizeEvent& e); //!< Run when the window is resized
		bool onMoved(WindowMovedEvent& e); //!< Moved window 
		bool onFocus(WindowFocusEvent& e); //!< Window Focus 
		bool onLostFocus(WindowLostFocusEvent& e); //!< Window lost focus
		
		bool onKeyPressed(KeyPressedEvent& e); //!< Runs the KeyPressed event 
		bool onKeyReleased(KeyReleasedEvent& e); //!< Runs the KeyRelease event

		bool onMouseMoved(MouseMovedEvent& e);
		bool onMouseDown(MouseButtonPressedEvent& e);
		bool onMouseUp(MouseButtonReleasedEvent& e);
		bool onMouseWheel(MouseScrolledEvent& e);



	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		

	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}