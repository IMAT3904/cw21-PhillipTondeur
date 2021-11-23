/**\file GLFWWIndowImpl.cpp */

#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImpl.h"
#include "platform/GLFW/GLFW_OpenGL_GC.h"
#include "systems/log.h"

namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS
	 Window* Window::create(const WindowProperties& properties)
	{
		return new GLFWWindowImpl(properties);
	}
#endif
	GLFWWindowImpl::GLFWWindowImpl(const WindowProperties& properties)
	{
		init(properties);
	}
	void GLFWWindowImpl::init(const WindowProperties& properties)
	{
		m_props = properties;

		m_aspectRatio = static_cast<float> (m_props.width) / static_cast<float> (m_props.height);

		if (m_props.isFullScreen)
		{
			Log::error("FullScreen not yet Implement");
		}
		else
		{
			m_native = glfwCreateWindow(m_props.width, m_props.height, m_props.title, nullptr, nullptr);
		}

		glfwSetWindowUserPointer(m_native, static_cast<void*>(&m_handler));

		m_graphicsContext.reset(new GLFW_OpenGL_GC(m_native));
		m_graphicsContext->init();

		glfwSetWindowCloseCallback(m_native, [](GLFWwindow* window)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onClose = handler->getOnCloseCallback();

				WindowCloseEvent e;
				onClose(e);

			}
		);
		glfwSetWindowSizeCallback(m_native,
			[](GLFWwindow* window, int newWidth, int newHeight)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onResize = handler->getOnResizeCallback();

				WindowResizeEvent e(newWidth, newHeight);
				onResize(e);
			}
		);
		glfwSetWindowPosCallback(m_native,
			[](GLFWwindow* window, int posX, int posY)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onMoved = handler->getOnMovedCallback();

				WindowMovedEvent e(posX,posY);
				onMoved(e);
			}
		);
		glfwSetWindowFocusCallback(m_native,
			[](GLFWwindow* window, int state)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

				if (state == GLFW_TRUE)
				{
					auto& onFocused = handler->getOnFocusCallback();
					WindowFocusEvent e;
					onFocused(e);
				}
				else if (state == GLFW_FALSE)
				{
					auto& onLostFocused = handler->getOnLostFocusCallback();
					WindowLostFocusEvent e;
					onLostFocused(e);
				}
			}
		);
		glfwSetKeyCallback(m_native,
			[](GLFWwindow* window, int keyCode, int scancode, int action, int mods)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				if (action == GLFW_PRESS)
				{
					auto& onKeyPress = handler->getOnKeyPressCallback();

					KeyPressedEvent e(keyCode, 0);
					onKeyPress(e);
				}
				else if (action == GLFW_REPEAT)
				{
					auto& onKeyPress = handler->getOnKeyPressCallback();

					KeyPressedEvent e(keyCode, 0);
					onKeyPress(e);
				}
				else if (action == GLFW_RELEASE)
				{
					auto& onKeyRelease = handler->getOnKeyReleaseCallback();

					KeyReleasedEvent e(keyCode);
					onKeyRelease(e);
				}
			}
		);
		glfwSetCursorPosCallback(m_native,
			[](GLFWwindow* window, double mouseX, double mouseY)
			{
				MouseMovedEvent e(static_cast<float>(mouseX), static_cast<float>(mouseY));

				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(window);
				auto& onMouseMoved = handler->getOnMouseMovedCallback();

				onMouseMoved(e);

			}
		);
		glfwSetMouseButtonCallback(m_native,
			[](GLFWwindow* window,int button, int action, int mods)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				if (action == GLFW_PRESS)
				{
					auto& onMousePressed = handler->getOnMouseDownCallback();

					MouseButtonPressedEvent e(button);
					onMousePressed(e);
				}
				else if (action == GLFW_RELEASE)
				{
					MouseButtonReleasedEvent e(button);
					auto& onMouseReleased = handler->getOnMouseUpCallback();

					onMouseReleased(e);
				}
			}
		);
		glfwSetScrollCallback(m_native,
			[](GLFWwindow* window, double xOffset, double yOffset)
			{
				MouseScrolledEvent e(static_cast<float>(xOffset), static_cast<float>(yOffset));
				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(window);

				auto& onMouseScrolled = handler->getOnMouseWheelCallback();

				onMouseScrolled(e);

			}
		);
	}

	void GLFWWindowImpl::close()
	{
		glfwDestroyWindow(m_native);
	}
	void GLFWWindowImpl::onUpdate(float timestep)
	{
		glfwPollEvents();
		m_graphicsContext->swapBuffers();
	}
	void GLFWWindowImpl::setVSync(bool VSync)
	{
		m_props.isVsync = VSync;
		if (m_props.isVsync) { glfwSwapInterval(1); }
		else { glfwSwapInterval(0); }

	}
}