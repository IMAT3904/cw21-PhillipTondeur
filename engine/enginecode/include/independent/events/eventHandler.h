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
		void setOnResizeCallBack(const std::function<bool(WindowResizeEvent&)>& fn) { m_onResizeCallback = fn; }
		void setOnFocusCallBack(const std::function<bool(WindowFocusEvent&)>& fn) { m_onFocusCallback = fn; }
		void setOnLostFocusCallBack(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onLostFocusCallback = fn; }
		void setOnWindowMovedCallBack(const std::function<bool(WindowMovedEvent&)>& fn) { m_onWindowMovedCallback = fn; }
		void setOnKeyPressCallBack(const std::function<bool(KeyPressedEvent&)>& fn) { m_onKeyDownCallback = fn; }
		void setOnKeyReleaseCallBack(const std::function<bool(KeyReleasedEvent&)>& fn) { m_onKeyUpCallback = fn; }
		void setOnKeyTypedCallBack(const std::function<bool(KeyTypedEvent&)>& fn) { m_onKeyTypedCallback = fn; }
		void setOnMouseDownCallBack(const std::function<bool(MouseButtonPressedEvent&)>& fn) { m_onMouseDownCallback = fn; }
		void setOnMouseUpCallBack(const std::function<bool(MouseButtonReleasedEvent&)>& fn) { m_onMouseUpCallback = fn; }
		void setOnMouseWheelCallBack(const std::function<bool(MouseScrolledEvent&)>& fn) { m_onMouseWheelCallback = fn; }
		void setOnMouseMovedCallBack(const std::function<bool(MouseMovedEvent&)>& fn) { m_onMouseMovedCallback = fn; }
		
		std::function<bool(WindowCloseEvent&)>& getOnCloseCallback() { return m_onCloseCallback; }
		std::function<bool(WindowResizeEvent&)>& getOnResizeCallback() { return m_onResizeCallback; }
		std::function<bool(WindowFocusEvent&)>& getOnFocusCallback() { return m_onFocusCallback; }
		std::function<bool(WindowLostFocusEvent&)>& getOnLostFocusCallback() { return m_onLostFocusCallback; }
		std::function<bool(WindowMovedEvent&)>& getOnMovedCallback() { return m_onWindowMovedCallback; }
		std::function<bool(KeyPressedEvent&)>& getOnKeyPressCallback() { return m_onKeyDownCallback; }
		std::function<bool(KeyReleasedEvent&)>& getOnKeyReleaseCallback() { return m_onKeyUpCallback; }
		std::function<bool(KeyTypedEvent&)>& getOnKeyTypedCallback() { return m_onKeyTypedCallback; }
		std::function<bool(MouseButtonPressedEvent&)>& getOnMouseDownCallback() { return m_onMouseDownCallback; }
		std::function<bool(MouseButtonReleasedEvent&)>& getOnMouseUpCallback() { return m_onMouseUpCallback; }
		std::function<bool(MouseScrolledEvent&)>& getOnMouseWheelCallback() { return m_onMouseWheelCallback; }
		std::function<bool(MouseMovedEvent&)>& getOnMouseMovedCallback() { return m_onMouseMovedCallback; }

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
		std::function<bool(MouseScrolledEvent&)> m_onMouseWheelCallback = std::bind(&EventHandler::defaultOnMouseWheel, this, std::placeholders::_1);
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