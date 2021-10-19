/**\file eventHandler.h*/

#pragma once
#include "events.h"

#include<functional>

//MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled

namespace Engine
{
	class EventHandler
	{
	public:
		void setOnCloseCallBack(const std::function<bool(WindowCloseEvent&)>& fn) { m_onCloseCallback = fn; }
		void setOnCloseCallBack(const std::function<bool(WindowCloseEvent&)>& fn) { m_onCloseCallback = fn; }
		std::function<bool(WindowCloseEvent&)>& getOnCloseCallback() { return m_onCloseCallback; }

	private:
		std::function<bool(WindowCloseEvent&)> m_onCloseCallback = std::bind(&EventHandler::defaultOnClose, this, std::placeholders::_1);
		std::function<bool(WindowResizeEvent&)> m_onResizeCallback = std::bind(&EventHandler::defaultOnResize, this, std::placeholders::_1);
		std::function<bool(WindowFocusEvent&)> m_onFocusCallback = std::bind(&EventHandler::defaultOnFocus, this, std::placeholders::_1);
		std::function<bool(WindowLostFocusEvent&)> m_onLostFocusCallback = std::bind(&EventHandler::defaultOnLostFocus, this, std::placeholders::_1);
		std::function<bool(WindowMovedEvent&)> m_onWindowMovedCallback = std::bind(&EventHandler::defaultOnWindowMoved, this, std::placeholders::_1);
		std::function<bool(KeyPressedEvent&)> m_onKeyDownCallback = std::bind(&EventHandler::defaultOnKeyPress, this, std::placeholders::_1);
		std::function<bool(KeyReleasedEvent&)> m_onKeyUpCallback = std::bind(&EventHandler::defaultOnKeyRelease, this, std::placeholders::_1);
		std::function<bool(KeyTypedEvent&)> m_onKeyTypedCallback = std::bind(&EventHandler::defaultOnKeyTyped, this, std::placeholders::_1);
		std::function<bool(MouseButtonPressedEvent&)> m_onMouseDownCallback = std::bind(&EventHandler::defaultOnMouseDown, this, std::placeholders::_1);
		std::function<bool(MouseButtonReleasedEvent&)> m_onMouseUpCallback = std::bind(&EventHandler::defaultOnMouseUp, this, std::placeholders::_1);
		std::function<bool(MouseScrolledEvent&)> m_onMouseMovedCallback = std::bind(&EventHandler::defaultOnMouseWheel, this, std::placeholders::_1);
		std::function<bool(MouseMovedEvent&)> m_onMouseMovedCallback = std::bind(&EventHandler::defaultOnMouseMoved, this, std::placeholders::_1);

		bool defaultOnClose(WindowCloseEvent& e) { return false; }
		bool defaultOnResize(WindowResizeEvent& e) { return false; }
		bool defaultOnFocus(WindowFocusEvent& e) { return false; }
		bool defaultOnLostFocus(WindowLostFocusEvent& e) { return false; }
		bool defaultOnWindowMoved(WindowMovedEvent& e) { return false; }
		bool defaultOnKeyPress(KeyPressedEvent& e) { return false; }
		bool defaultOnKeyRelease(KeyReleasedEvent& e) { return false; }
		bool defaultOnKeyTyped(KeyTypedEvent& e) { return false; }
		bool defaultOnMouseDown(MouseButtonPressedEvent& e) { return false; }
		bool defaultOnMouseUp(MouseButtonReleasedEvent& e) { return false; }
		bool defaultOnMouseWheel(MouseScrolledEvent& e) { return false; }
		bool defaultOnMouseMoved(MouseMovedEvent& e) { return false; }
	};
}