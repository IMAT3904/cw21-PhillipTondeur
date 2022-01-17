/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

#include <glad/glad.h>

#include "core/application.h"
#include "platform/GLFW/GLFWCodes.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include "rendering/indexBuffer.h"
#include "rendering/vertexBuffer.h"
#include "rendering/vertexArray.h"
#include "rendering/subTexture.h"
#include "rendering/texture.h"
#include "rendering/shader.h"

#include "rendering/Renderer3D.h"
#include "rendering/Renderer2D.h"

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


		//stop Windows system
		m_windowsSystem->stop();
				//Stop Logger
		m_logSystem->stop();
	}


	void Application::run()
	{
#pragma region TEXTURES

		std::shared_ptr<Texture> letterTexture;
		//letterTexture.reset(new OpenGLTexture("assets/textures/letterAndNumberCube.png"));
		letterTexture.reset( Texture::create("assets/textures/letterCube.png")); 

		std::shared_ptr<Texture> numberTexture;
		numberTexture.reset(Texture::create("assets/textures/numberCube.png"));

		unsigned char whitePx[4] = { 255, 255, 255, 255 };
		std::shared_ptr<Texture> plainWhiteTexture;
		plainWhiteTexture.reset(Texture::create(1, 1, 4, whitePx)); // Check after fix

		//SubTexture letterCube(letterTexture, { 0.f,0.f }, { 1.0f,0.5f });
		//SubTexture numberCube(letterTexture, { 0.f,0.5f }, { 1.0f,1.0f });
#pragma endregion
#pragma region RAW_DATA

		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f, 0.f,    0.f,
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f, 0.f,    0.5f,
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f, 0.33f,  0.5f,
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f, 0.33f,  0.f,
				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f, 0.33f,  0.5f,
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f, 0.66f,  0.5f,
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f, 0.66f,  0.f,
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f, 0.33,   0.f,
				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f, 1.f,    0.f,
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f, 0.66f,  0.f,
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f, 0.66f,  0.5f,
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f, 1.0f,   0.5f,
				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f, 0.f,    0.5f,
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f, 0.f,    1.0f,
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f, 0.33f,  1.0f,
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f, 0.3f,   0.5f,
				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f, 0.66f,  0.5f,
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f, 0.33f,  0.5f,
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f, 0.33f,  1.0f,
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f, 0.66f,  1.0f,
				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f, 1.0f,   1.0f,
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f, 1.0f,   0.5f,
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f, 0.66f,  0.5f,
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f, 0.66f,  1.0f
		};

		float pyramidVertices[8 * 16] = {
			//	 <------ Pos ------>  <--- colour ---> 
			-0.5f, -0.5f, -0.5f, 0.f,		-1.f, 0.f,  0.f, 0.f,  //  square Magneta
			 0.5f, -0.5f, -0.5f, 0.f,		-1.f, 0.f,  0.f, 0.5f,
			 0.5f, -0.5f,  0.5f, 0.f,		-1.f, 0.f,  0.33f, 0.5f,
			-0.5f, -0.5f,  0.5f, 0.f,		-1.f, 0.f,  0.33f, 0.f,

			-0.5f, -0.5f, -0.5f, -0.8944f,  0.4472f, 0.f,  0.33f, 1.f,  //triangle Green
			-0.5f, -0.5f,  0.5f, -0.8944f,  0.4472f, 0.f,  0.66f, 1.f,
			 0.0f,  0.5f,  0.0f, -0.8944f,  0.4472f, 0.f,  0.495, 0.f,

			-0.5f, -0.5f,  0.5f,  0.f,		0.4472f, 0.8944f,  0.f, 0.f, ////triangle Red
			 0.5f, -0.5f,  0.5f,  0.f,		0.4472f, 0.8944f,  0.f, 0.f,
			 0.0f,  0.5f,  0.0f,  0.f,		0.4472f, 0.8944f,  0.f, 0.f,

			 0.5f, -0.5f,  0.5f,  0.8944f,	0.4472f, 0.f,  0.f, 0.f, // //  triangle Yellow
			 0.5f, -0.5f, -0.5f,  0.8944f,	0.4472f,  0.f, 0.f, 0.f,
			 0.0f,  0.5f,  0.0f,  0.8944f,	0.4472f,  0.f, 0.f, 0.f,

			 0.5f, -0.5f, -0.5f,  0.f,		0.4472f, -0.8944f,   0.f, 0.f, //triangle Blue
			-0.5f, -0.5f, -0.5f,  0.f,		0.4472f, -0.8944f,   0.f, 0.f,
			 0.0f,  0.5f,  0.0f,  0.f,		0.4472f, -0.8944f,  0.f, 0.f,
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
		std::shared_ptr<VertexArray> cubeVAO;
		std::shared_ptr<VertexBuffer> cubeVBO;
		std::shared_ptr<IndexBuffer> cubeIBO;

		cubeVAO.reset(VertexArray::create());

		BufferLayout cubeLayout = { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 };
		cubeVBO.reset(VertexBuffer::create(cubeVertices, sizeof(cubeVertices), cubeLayout));

		cubeVAO->addVertexBuffer(cubeVBO);

		cubeIBO.reset(IndexBuffer::create(cubeIndices, 36));
		cubeVAO->setIndexBuffer(cubeIBO);


		std::shared_ptr<VertexArray> pyramidVAO;
		std::shared_ptr<VertexBuffer> pyramidVBO;
		std::shared_ptr<IndexBuffer> pyramidIBO;

		pyramidVAO.reset(VertexArray::create());

		pyramidVBO.reset(VertexBuffer::create(pyramidVertices, sizeof(pyramidVertices), cubeLayout));

		pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);

		pyramidVAO->setIndexBuffer(pyramidIBO);
		
#pragma endregion


#pragma region SHADERS
		
		//FCShader.reset(new OpenGLShader("./assets/shaders/flatColour.vert", "./assets/shaders/flatColour.frag"));

		std::shared_ptr<Shader> TPShader;
		TPShader.reset(Shader::create("./assets/shaders/texturedPhong.glsl"));
#pragma endregion 

#pragma region MATERIALS

		std::shared_ptr<Material> pyramidMat;
		pyramidMat.reset(new Material(TPShader, { 1.0f, 0.0f, 0.0f, 1.f }));
		std::shared_ptr<Material> letterCubeMat;
		letterCubeMat.reset(new Material(TPShader, letterTexture));
		std::shared_ptr<Material> numberCubeMat;
		numberCubeMat.reset(new Material(TPShader, numberTexture));

		
#pragma endregion
		
		glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

		////Camera UBO
		//uint32_t blockNumber = 0; 
		//
		//UniformBufferLayout camLayout = { {"u_projection", ShaderDataType::Mat4}, {"u_view", ShaderDataType::Mat4} };

		//std::shared_ptr<UniformBufferLayout> cameraUBO;
		//cameraUBO.reset(UniformBufferLayout::create(camLayout));

		//cameraUBO->attachShaderBlock(FCShader, "b_camera");
		//cameraUBO->attachShaderBlock(TPShader, "b_camera");

		//cameraUBO->uploadData("u_projection", glm::value_ptr(projection));
		//cameraUBO->uploadData("u_view", glm::value_ptr(view));
		//blockNumber++;
		//glm::vec3 lightColour(1.f, 1.f, 1.f);
		//glm::vec3 lightPos(1.f, 4.f, 6.f);
		//glm::vec3 viewPos(0.f, 0.f, 0.f);

		//uint32_t lightsUBO;
		//uint32_t lightsDataSize = sizeof(glm::vec4) * 3;

		//glGenBuffers(1, &lightsUBO);
		//glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		//glBufferData(GL_UNIFORM_BUFFER, lightsDataSize, nullptr, GL_DYNAMIC_DRAW);
		//glBindBufferRange(GL_UNIFORM_BUFFER, blockNumber, lightsUBO, 0, lightsDataSize);

		//uint32_t blockIndex = glGetUniformBlockIndex(TPShader->getID(), "b_lights");
		//glUniformBlockBinding(TPShader->getID(), blockIndex, blockNumber);

		//glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(lightPos));
		//glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(viewPos));
		//glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec3), glm::value_ptr(lightColour));

		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

		float timestep = 0.f;

		glm::mat4 view2D = glm::mat4(1.f);
		glm::mat4 projection2D = glm::ortho(0.f, static_cast<float>(m_window->getHeight()), 0.f, static_cast<float>(m_window->getWidth()));


		SceneWideUniforms swu3D;


		glm::vec3 lightData[3] = { {1.f, 1.f, 1.f }, {-2.f, 4.f, -6.f} ,{0.f,0.f,0.f } };
		swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(view)));
		swu3D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(projection)));
		swu3D["u_lightColour"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightData[0])));
		swu3D["u_lightPos"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightData[1])));
		swu3D["u_viewPos"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightData[2])));
		
		SceneWideUniforms swu2D;
		swu2D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(view2D)));
		swu2D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(projection2D)));

		Renderer3D::init();
		Renderer2D::init();

		Quad quads[6] =
		{
		Quad::createCentreHalfExtents({ 400.f, 200.f }, { 100.f, 50.f }),
		Quad::createCentreHalfExtents({ 200.f, 200.f }, { 50.f, 100.f }),
		Quad::createCentreHalfExtents({ 400.f, 800.f }, { 75.f, 75.f }),
		Quad::createCentreHalfExtents({ 100.f, 200.f }, { 100.f, 50.f }),
		Quad::createCentreHalfExtents({ 500.f, 100.f }, { 50.f, 25.f }),
		Quad::createCentreHalfExtents({ 600.f, 1000.f }, { 75.f, 15.f })
		};
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		while (m_running)
		{
			
			timestep = m_timer->getElapsedTime();
			m_timer->reset();
			//Log::trace("FPS {0}", 1.0f / timestep);
			//if (InputPoller::isKeyPressed(NG_KEY_W)) Log::error("W Pressed");
			//if (InputPoller::isMouseButtonPressed(NG_MOUSE_BUTTON_1)) Log::error("Left Mouse Button Pressed");
			//Log::trace("Current mouse pos: ({0}, {1})", InputPoller::getMouseX(), InputPoller::getMouseY());

			for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0, 0.f)); }
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnable(GL_DEPTH_TEST);
			Renderer3D::begin(swu3D);
			
			Renderer3D::submit(pyramidVAO, pyramidMat, models[0]);
			Renderer3D::submit(cubeVAO, letterCubeMat, models[1]);
			Renderer3D::submit(cubeVAO, numberCubeMat, models[2]);
			Renderer3D::end();
	
			

			/*plainWhiteTexture->bindToUnit(0);

			glUseProgram(TPShader->getID());
			glBindVertexArray(pyramidVAO->getID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO->getID());

		
			TPShader->uploadMat4("u_view", view);
			TPShader->uploadMat4("u_projection", projection);

			TPShader->uploadFloat3("u_lightColour", glm::vec3(1.f, 1.f, 1.f));
			TPShader->uploadFloat3("u_lightPos", glm::vec3(1.f, 1.f, 1.f));
			TPShader->uploadFloat3("u_viewPos", glm::vec3(0.f, 0.f, 0.f));

			TPShader->uploadMat4("u_model", models[0]);
			TPShader->uploadFloat4("u_tint", { 0.4f, 0.7f, 0.3f, 1.f });
			TPShader->uploadInt("u_texData", 0);*/

			//glDrawElements(GL_TRIANGLES, pyramidVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

			glBindVertexArray(cubeVAO->getID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO->getID());

			TPShader->uploadMat4("u_model", models[1]);

			letterTexture->bindToUnit(0);
			TPShader->uploadFloat4("u_tint", { 1.f, 1.f, 1.f, 1.f });
			TPShader->uploadInt("u_texData", 0);

			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

			TPShader->uploadMat4("u_model", models[2]);
			numberTexture->bindToUnit(0);

			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
			
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			Renderer2D::begin(swu2D);

			Renderer2D::submit(quads[0], { 0.f,1.f,0.f,1.f });
			Renderer2D::submit(quads[1], letterTexture);
			Renderer2D::submit(quads[2], { 0.5f,0.5f,0.f,1.f }, numberTexture);
			Renderer2D::submit(quads[3], { 0.5f,0.5f,0.f,0.5f }, numberTexture, 45.f, true);
			Renderer2D::submit(quads[3], { 0.5f,0.5f,0.f,1.f }, numberTexture, glm::radians(-45.f));
			Renderer2D::submit(quads[4], { 1.f,1.f,0.f,1.f }, 30.f, true);
			Renderer2D::submit(quads[5], { 0.5f,0.5f,0.f,1.f }, letterTexture, 120.f, true);


			Renderer2D::end();
			m_window->onUpdate(timestep);
		}


		

	

	};

}
