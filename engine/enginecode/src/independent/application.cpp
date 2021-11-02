/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		// Start Systems

		//Start log
		m_logSystem.reset(new Log);
		m_logSystem->start();

#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();

		//reset timer (not a system)
		m_timer.reset(new ChronoTimer);
		m_timer->start();
		
		WindowProperties props("My Game Engine", 1024, 800);
		
		m_window.reset(Window::create(props));

		m_window->getEventHandler().setOnCloseCallBack(std::bind(&Application:: onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnResizeCallBack(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowMovedCallBack(std::bind(&Application::onMoved, this, std::placeholders::_1));
		m_window->getEventHandler().setOnFocusCallBack(std::bind(&Application::onFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnLostFocusCallBack(std::bind(&Application::onLostFocus, this, std::placeholders::_1));

		m_window->getEventHandler().setOnKeyPressCallBack(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleaseCallBack(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));

		m_window->getEventHandler().setOnMouseMovedCallBack(std::bind(&Application::onMouseMoved, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseDownCallBack(std::bind(&Application::onMouseDown, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseUpCallBack(std::bind(&Application::onMouseUp, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseWheelCallBack(std::bind(&Application::onMouseWheel, this, std::placeholders::_1));

		m_timer->reset();


	}

	bool Application::onClose(WindowCloseEvent& e)
	{
		e.handle(true);
		m_running = false;
		return e.handled();
		
	}

	bool Application::onResize(WindowResizeEvent& e)
	{
		e.handle(true);
		auto& size = e.getSize();
		Log::info("Window Resize event:({0}, {1})", size.x, size.y);
		return e.handled();
	}

	bool Application::onMoved(WindowMovedEvent& e)
	{
		e.handle(true);
		auto& pos = e.getPos();
		Log::info("Window Resize event:({0}, {1})", pos.x, pos.y);
		return e.handled();
	}

	bool Application::onFocus(WindowFocusEvent& e)
	{
		e.handle(true);
		Log::info("Gained focus");
		return e.handled();
	}

	bool Application::onLostFocus(WindowLostFocusEvent& e)
	{
		e.handle(true);
		Log::info("Lost focus");
		return e.handled();
	}

	bool Application::onKeyPressed(KeyPressedEvent& e)
	{
		e.handle(true);
		Log::info("Key Pressed event:({0}, {1})", e.getKeyCode(), e.getRepeatCount());
		return e.handled();
	}

	bool Application::onKeyReleased(KeyReleasedEvent& e)
	{
		e.handle(true);
		Log::info("Key Released event:({0})", e.getKeyCode());
		return e.handled();
	}

	bool Application::onMouseMoved(MouseMovedEvent& e)
	{
		e.handle(true);
		auto& pos = e.getPos();
		Log::info("Mouse Moved Event: ({0}, {1})", pos.x, pos.y);
		return e.handled();
	}

	bool Application::onMouseDown(MouseButtonPressedEvent& e)
	{
		e.handle(true);
		Log::info("Mouse button Pressed event:({0})", e.getButton());
		return e.handled();
	}

	bool Application::onMouseUp(MouseButtonReleasedEvent& e)
	{
		e.handle(true);
		Log::info("Mouse button Released event:({0})", e.getButton());
		return e.handled();
	}

	bool Application::onMouseWheel(MouseScrolledEvent& e)
	{
		e.handle(true);
		Log::info("Mouse Wheel Event: {0}", e.getYOffset());
		return e.handled();
	}



	Application::~Application()
	{
		//Stop systems 

		//Stop Logger
		m_logSystem->stop();
		//stop Windows system
		m_windowsSystem->stop();

	}


	void Application::run()
	{
		float timestep = 0.f;
		float accumTime = 0.f;

		while (m_running)
		{
			timestep = m_timer->getElapsedTime();
			m_timer->reset();
			//Log::trace("FPS {0}", 1.0f / timestep);
			
			m_window->onUpdate(timestep);
			//frame stuff

			
		};
	}

}
