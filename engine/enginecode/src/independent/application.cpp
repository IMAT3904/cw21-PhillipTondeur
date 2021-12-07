/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

#include <glad/glad.h>

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "rendering/subTexture.h"
#include "rendering/uniformBuffer.h"
#include "rendering/IndexBuffer.h"

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


		InputPoller::setNativeWindow(m_window->getNativeWindow());
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
#pragma region TEXTURES

		std::shared_ptr<OpenGLTexture> letterTexture;
		letterTexture.reset(new OpenGLTexture("assets/textures/letterAndNumberCube.png"));
		//std::shared_ptr<OpenGLTexture> numberTexture;
		//numberTexture.reset(new OpenGLTexture("assets/textures/numberCube.png"));

		SubTexture letterCube(letterTexture, { 0.f,0.f }, { 1.0f,0.5f });
		SubTexture numberCube(letterTexture, { 0.f,0.5f }, { 1.0f,1.0f });
#pragma endregion
#pragma region RAW_DATA

		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f, numberCube.transformU(0.f),    numberCube.transformV( 0.f),
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f, numberCube.transformU(0.f),    numberCube.transformV( 0.5f),
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f, numberCube.transformU(0.33f),  numberCube.transformV( 0.5f),
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f, numberCube.transformU(0.33f),  numberCube.transformV( 0.f),
				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f, numberCube.transformU(0.33f),  numberCube.transformV( 0.5f),
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f, numberCube.transformU(0.66f),  numberCube.transformV( 0.5f),
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f, numberCube.transformU(0.66f),  numberCube.transformV( 0.f),
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f, numberCube.transformU(0.33),   numberCube.transformV( 0.f),
				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f, numberCube.transformU(1.f),    numberCube.transformV( 0.f),
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f, numberCube.transformU(0.66f),  numberCube.transformV( 0.f),
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f, numberCube.transformU(0.66f),  numberCube.transformV( 0.5f),
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f, numberCube.transformU(1.0f),   numberCube.transformV( 0.5f),
				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f, numberCube.transformU(0.f),    numberCube.transformV( 0.5f),
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f, numberCube.transformU(0.f),    numberCube.transformV( 1.0f),
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f, numberCube.transformU(0.33f),  numberCube.transformV( 1.0f),
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f, numberCube.transformU(0.3f),   numberCube.transformV( 0.5f),
				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f, numberCube.transformU(0.66f),  numberCube.transformV( 0.5f),
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f, numberCube.transformU(0.33f),  numberCube.transformV( 0.5f),
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f, numberCube.transformU(0.33f),  numberCube.transformV( 1.0f),
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f, numberCube.transformU(0.66f),  numberCube.transformV( 1.0f),
				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f, numberCube.transformU(1.0f),   numberCube.transformV( 1.0f),
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f, numberCube.transformU(1.0f),   numberCube.transformV( 0.5f),
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f, numberCube.transformU(0.66f),  numberCube.transformV( 0.5f),
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f, numberCube.transformU(0.66f),  numberCube.transformV( 1.0f)
		};

		float pyramidVertices[6 * 16] = {
			//	 <------ Pos ------>  <--- colour ---> 
				-0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f, //  square Magneta
				 0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f,
				 0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,
				-0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,

				-0.5f, -0.5f, -0.5f,  0.2f, 0.8f, 0.2f,  //triangle Green
				-0.5f, -0.5f,  0.5f,  0.2f, 0.8f, 0.2f,
				 0.0f,  0.5f,  0.0f,  0.2f, 0.8f, 0.2f,

				-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f, //triangle Red
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,
				 0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.f,

				 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.2f, //  triangle Yellow
				 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.2f,
				 0.0f,  0.5f,  0.0f,  0.8f, 0.8f, 0.2f,

				 0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,//  triangle Blue
				-0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.2f, 1.0f
		};

		uint32_t pyramidIndices[3 * 6] =
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

		uint32_t cubeIndices[3 * 12] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
#pragma endregion

#pragma region GL_BUFFERS
		std::shared_ptr<OpenGLVertexArray> cubeVAO;
		std::shared_ptr<OpenGLVertexBuffer> cubeVBO;
		std::shared_ptr<IndexBuffer> cubeIBO;

		cubeVAO.reset(new OpenGLVertexArray);

		VertexBufferLayout cubeBL = { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 }; //creating a buffer from it's initialiser list 
		cubeVBO.reset(new OpenGLVertexBuffer(cubeVertices, sizeof(cubeVertices), cubeBL));

		cubeIBO.reset( IndexBuffer::create(cubeIndices, 36));

		cubeVAO->addVertexBuffer(cubeVBO);
		cubeVAO->setIndexBuffer(cubeIBO);



		std::shared_ptr<OpenGLVertexArray> pyramidVAO;
		std::shared_ptr<OpenGLVertexBuffer> pyramidVBO;
		std::shared_ptr<IndexBuffer> pyramidIBO;

		pyramidVAO.reset(new OpenGLVertexArray);
		VertexBufferLayout pyramidBL = { ShaderDataType::Float3, ShaderDataType::Float3 };

		pyramidVBO.reset(new OpenGLVertexBuffer(pyramidVertices, sizeof(pyramidVertices), pyramidBL));

		pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->setIndexBuffer(pyramidIBO);
		
#pragma endregion


#pragma region SHADERS
		std::shared_ptr<OpenGLShader> FCShader;
		FCShader.reset(new OpenGLShader("./assets/shaders/flatColour.glsl"));
		//FCShader.reset(new OpenGLShader("./assets/shaders/flatColour.vert", "./assets/shaders/flatColour.frag"));

		std::shared_ptr<OpenGLShader> TPShader;
		TPShader.reset(new OpenGLShader("./assets/shaders/texturedPhong.glsl"));
#pragma endregion 


		glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

		//Camera UBO
		uint32_t blockNumber = 0; 
		
		UniformBufferLayout camLayout = { {"u_projection", ShaderDataType::Mat4}, {"u_view", ShaderDataType::Mat4} };

		std::shared_ptr<UniformBuffer> cameraUBO;
		cameraUBO.reset(UniformBuffer::create(camLayout));

		cameraUBO->attachShaderBlock(FCShader, "b_camera");
		cameraUBO->attachShaderBlock(TPShader, "b_camera");

		cameraUBO->uploadData("u_projection", glm::value_ptr(projection));
		cameraUBO->uploadData("u_view", glm::value_ptr(view));
		blockNumber++;
		glm::vec3 lightColour(1.f, 1.f, 1.f);
		glm::vec3 lightPos(1.f, 4.f, 6.f);
		glm::vec3 viewPos(0.f, 0.f, 0.f);

		uint32_t lightsUBO;
		uint32_t lightsDataSize = sizeof(glm::vec4) * 3;

		glGenBuffers(1, &lightsUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		glBufferData(GL_UNIFORM_BUFFER, lightsDataSize, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, blockNumber, lightsUBO, 0, lightsDataSize);

		uint32_t blockIndex = glGetUniformBlockIndex(TPShader->getID(), "b_lights");
		glUniformBlockBinding(TPShader->getID(), blockIndex, blockNumber);

		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(lightPos));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(viewPos));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec3), glm::value_ptr(lightColour));

		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

		float timestep = 0.f;

		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		while (m_running)
		{
			timestep = m_timer->getElapsedTime();
			m_timer->reset();
			//Log::trace("FPS {0}", 1.0f / timestep);
			//if (InputPoller::isKeyPressed(NG_KEY_W)) Log::error("W Pressed");
			//if (InputPoller::isMouseButtonPressed(NG_MOUSE_BUTTON_1)) Log::error("Left Mouse Button Pressed");
			//Log::trace("Current mouse pos: ({0}, {1})", InputPoller::getMouseX(), InputPoller::getMouseY());

			for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0, 0.f)); }

			// Do frame stuff
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(FCShader->getID());
			glBindVertexArray(pyramidVAO->getrenderID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO->getrenderID());

			GLuint uniformLocation;

			uniformLocation = glGetUniformLocation(FCShader->getID(), "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[0])); // Must include <glm/gtc/type_ptr.hpp>


			glDrawElements(GL_TRIANGLES, pyramidVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

			glUseProgram(TPShader->getID());

			glBindVertexArray(cubeVAO->getrenderID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO->getrenderID());


			uniformLocation = glGetUniformLocation(TPShader->getID(), "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[1]));

			glBindTexture(GL_TEXTURE_2D, letterTexture->getID());
			uniformLocation = glGetUniformLocation(TPShader->getID(), "u_texData");
			glUniform1i(uniformLocation, 0);

			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

			uniformLocation = glGetUniformLocation(TPShader->getID(), "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[2]));

			//glBindTexture(GL_TEXTURE_2D, numberTexture->getID());

			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
			
			m_window->onUpdate(timestep);
		}


		

	

	};

}
