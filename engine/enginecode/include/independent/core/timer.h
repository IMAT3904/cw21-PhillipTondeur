/** \file timer.h*/

#pragma once

#include <chrono>

namespace Engine
{

	/**
	\class Time - interface timer class
	*/

	class Timer
	{
	public:
		virtual void start() = 0; //!< Start Timer
		virtual void reset() = 0; //!< Reset Timer
		virtual float getElapsedTime() = 0; //!< Get the time elapsed since the start or restart 
	};

	/**
	\class ChronoTime - chrono timer class
	*/
	
	class ChronoTimer : public Timer
	{
	public:
		virtual inline void start () override {m_startPoint = std::chrono::high_resolution_clock::now(); }
		virtual inline void reset() override {m_endPoint = std::chrono::high_resolution_clock::now(); }
		float getElapsedTime() override
		{
			m_endPoint = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::milli> elapsed = m_endPoint - m_startPoint;
			return elapsed.count() / 1000.f;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_endPoint;
	};

}
