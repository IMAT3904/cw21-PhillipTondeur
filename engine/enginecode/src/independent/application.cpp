/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

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

	}

	Application::~Application()
	{
		//Stop systems 

		//Stop Logger
		m_logSystem->stop();
	}


	void Application::run()
	{
		while (m_running)
		{
			Log::trace("Hello world! {0} {1}", 42, "I am a string");
		};
	}

}
