/** \file timer.h*/

#pragma once

#include <chrono>

namespace Engine
{
	/**
	\class ChronoTime - chrono timer class
	*/

	class ChronoTimer
	{
	public:
		inline void start (){m_startPoint = std::chrono::high_resolution_clock::now(); }
		inline void reset() {m_endPoint = std::chrono::high_resolution_clock::now(); }
		float getElapsedTime()
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
