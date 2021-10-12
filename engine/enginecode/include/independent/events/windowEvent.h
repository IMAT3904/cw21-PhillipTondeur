/* \file windowEvent.h */
#pragma once


#include "event.h"

#include<glm/glm.hpp>


namespace Engine
{
	class WindowCloseEvent : public Event
	{
	public:
		static EventType getStaticType() { return EventType::WindowClose; } //!< Returns static type
		virtual inline  EventType getEventtype() const override { return EventType::WindowClose; } //!< Get the event type 
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags.
	};

	
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int32_t width, int32_t height) : m_width(width), m_height(height) {}
		static EventType getStaticType() { return EventType::WindowResize; } //!< Returns static type
		virtual inline  EventType getEventtype() const override { return EventType::WindowResize; } //!< Get the event type 
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags.
	private:
		int32_t m_width; //!< Window width after resize
		int32_t m_height; //!< Window height after resize
	};
}