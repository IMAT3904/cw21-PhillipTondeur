#pragma once

#include <gtest/gtest.h>

#include "events/eventHandler.h"
 

class MockApplication
{

public:
	void setCallback()
	{
		m_handler.setOnCloseCallBack(std::bind(&MockApplication::onClose, this, std::placeholders::_1));
	}
	Engine::EventHandler m_handler;
private:
	//Engine::EventHandler m_handler;
	bool onClose(Engine::WindowCloseEvent& e)
	{
		e.handle(true);
		return e.handled();
	}
};