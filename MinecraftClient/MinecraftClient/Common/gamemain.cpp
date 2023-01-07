#include "gamemain.h"
#include "GLFramework/GLShader.h"
#include "Primitive/Cube.h"
#include "Common/image.h"
#include "Utils/UtilsCubemap.h"
#include "stb/stb_image.h"
#include "Event/EventHandler.h"
#include "InputSystem.h"
#include "Camera/FPSCamera.h"
#include "VirtualKeyCodes.h"
#include "Primitive/Chunk.h"
#include "World/World.h"
namespace GNF::Common
{
	GameMain::GameMain() : camera(new Camera::FPSCamera()), m_inputSystem(new Input::InputSystem())
	{
		pWindow = Window::CreateWindow();

		pWindow->OnMouseMove += Event::EventHandler::Bind(&GameMain::MouseMoved, this);
		pWindow->KeyPressed += Event::EventHandler::Bind(&GameMain::OnKeyPressed, this);
		pWindow->MousePressed += Event::EventHandler::Bind(&GameMain::OnMousePressed, this);
	}

	void GameMain::OnMousePressed(const MousePressedEventArgs& e)
	{
		if (e.action == GLFW_PRESS)
		{
			if (e.button == GLFW_MOUSE_BUTTON_LEFT)
			{
				m_inputSystem->MouseKeyPressed(Input::MOUSE_KEY_CODE::LEFT_BUTTON);
			}
			
		}
		else
		{
			if (e.button == GLFW_MOUSE_BUTTON_LEFT)
			{
				m_inputSystem->MouseKeyReleased(Input::MOUSE_KEY_CODE::LEFT_BUTTON);
			}
		}
	}

	Input::IInputSystem* GameMain::GetInputSystem()
	{
		return m_inputSystem.get();
	}

	GameMain* GameMain::GetInstance()
	{
		return g_game.get();
	}
	GameMain* GameMain::Build()
	{
		g_game.reset(new GameMain());
		return g_game.get();
	}
	void GameMain::OnKeyPressed(const KeyPressedEventArgs& e)
	{
		switch (e.action)
		{
			case GLFW_PRESS:
				m_inputSystem->KeyPressed(e.keyCode);
				break;
			case GLFW_RELEASE:
				m_inputSystem->KeyReleased(e.keyCode);
				break;
		}
	}

	void GameMain::MouseMoved(const MouseMoveEventArgs& e)
	{
		
		if (firstMouse)
		{
			lastX = e.posx;
			lastY = e.posy;
			firstMouse = false;
		}

		float xOffSet = e.posx - lastX;
		float yOffSet = lastY - e.posy;
		lastX = e.posx;
		lastY = e.posy;

		if (!e.isCursorModeEnable)
			return;

		m_inputSystem->MouseMoved(e.posx, e.posy);
	}

	struct PerFrameData
	{
		glm::mat4 model;
		glm::mat4 mvp;
		glm::vec4 cameraPos;
	};

	void FpsCounter()
	{
		static double lastTime = glfwGetTime();
		static int nbFrames = 0;
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("%d fps\n", nbFrames);
			nbFrames = 0;
			lastTime += 1.0;
		}
	}

	int GameMain::Run()
	{


		GLShader skyVertex("Shaders/skybox.vert");
		GLShader skyPixel("Shaders/skybox.frag");
		GLProgram skyProgram(skyVertex, skyPixel);


		GLShader vertexShader("Shaders/basicvertex.vert");
		GLShader pixelShader("Shaders/basicfrag.frag");
		GLProgram program(vertexShader, pixelShader);
		program.useProgram();



		const GLsizeiptr kUniformBufferSize = sizeof(PerFrameData);

		GLuint perFrameDataBuffer;
		glCreateBuffers(1, &perFrameDataBuffer);
		glNamedBufferStorage(perFrameDataBuffer, kUniformBufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, perFrameDataBuffer, 0, kUniformBufferSize);


	
		//# ------------------

		GLuint cubemapTex;
		
		Bitmap* sky = nullptr;

		loadImage("assets/textures/sky.jpeg", &sky,false);

	
		/*
		int w, h, comp;
		const float* img = stbi_loadf("assets/textures/sky.jpeg", &w, &h, &comp, 3);
		Bitmap sky(w, h, comp, eBitmapFormat_Float, img);
		*/
		Bitmap mappedSky = convertEquirectangularMapToVerticalCross(*sky);

		Bitmap cubemap = convertVerticalCrossToCubeMapFaces(mappedSky);

		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &cubemapTex);
		glTextureParameteri(cubemapTex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(cubemapTex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(cubemapTex, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTextureParameteri(cubemapTex, GL_TEXTURE_BASE_LEVEL, 0);
		glTextureParameteri(cubemapTex, GL_TEXTURE_MAX_LEVEL, 0);
		glTextureParameteri(cubemapTex, GL_TEXTURE_MAX_LEVEL, 0);
		glTextureParameteri(cubemapTex, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(cubemapTex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureStorage2D(cubemapTex, 1, GL_RGB32F, cubemap.w_, cubemap.h_);
		const uint8_t* data = cubemap.data_.data();

		for (unsigned i = 0; i != 6; ++i)
		{
			glTextureSubImage3D(cubemapTex, 0, 0, 0, i, cubemap.w_, cubemap.h_, 1, GL_RGB, GL_FLOAT, data);
			data += cubemap.w_ * cubemap.h_ * cubemap.comp_ * Bitmap::getBytesPerComponent(cubemap.fmt_);
		}

		glBindTextures(1, 1, &cubemapTex);

		//# ------------------
		Bitmap* bitmap = nullptr;
		loadImage("assets/textures/grass_side.png", &bitmap);

		GLuint texture = createTextureFromBitmap((*bitmap), TEXTURE_2D);

		glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, texture);

		const glm::mat4 p = glm::perspective(45.0f, float((float)640 / (float)480), 0.1f, 1000.0f);




		glEnable(GL_DEPTH_TEST);
		Primitive::Cube cube(1, 0.5, { 0,0,0 });
		
		
		auto world = World::Build();

		//std::vector<std::unique_ptr<Primitive::Chunk>> chunks;
		/*
		auto t = Primitive::Chunk({ 0,0,0 });
		t.GenerateChunk();
		t.GenerateVAOVBO();

		auto iSize = t.SizeOfIndices();
		*/
		float deltaTime = 0.0f;	// Time between current frame and last frame
		float lastFrame = 0.0f; // Time of last frame

		while (!pWindow->ShouldClose())
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			FpsCounter();

			camera->Update(deltaTime);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glClearColor(1.0f, 0, 0, 1.f);
			{
				program.useProgram();

				//t.BindVAO();


				//const glm::mat4 m = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, -4.5f)), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
				
				const PerFrameData perFrameData = { .model = glm::mat4(1.0f), .mvp = camera->GetViewProjMatrix(), .cameraPos = glm::vec4(camera->GetPosition(),1.0f)};

				glNamedBufferSubData(perFrameDataBuffer, 0, kUniformBufferSize, &perFrameData);
				//cube.BindVAO();
				//glDrawElements(GL_TRIANGLES, cube.SizeOfIndices(), GL_UNSIGNED_INT, nullptr);
				for (auto& chx : *(world->GetChunks()))
				{
					for (auto& chy : chx)
					{
						for (auto& chz : chy)
						{
							chz->BindVAO();
							glDrawElements(GL_TRIANGLES, chz->SizeOfIndices(), GL_UNSIGNED_INT, nullptr);

						}
					}
				}
				/*
				for (int ch = 0; ch < world.GetChunkSize(); ch++)
				{
					auto chunk = world[ch];
					chunk.BindVAO();
					glDrawElements(GL_TRIANGLES, chunk.SizeOfIndices(), GL_UNSIGNED_INT, nullptr);

				*/
				//glDrawElements(GL_TRIANGLES, t.SizeOfIndices(), GL_UNSIGNED_INT, nullptr);
			}
			/*
			{
				for (int i = 0; i < chunks.size(); i++)
				{
					chunks[i]->BindVAO();

					glDrawElements(GL_TRIANGLES, chunks[i]->SizeOfIndices(), GL_UNSIGNED_INT, nullptr);
				}
			}*/
			{
				glm::mat4 m = glm::scale(glm::mat4(1.0f), glm::vec3(600.0f));
				m = glm::rotate(m, -float(3.14 / 2), glm::vec3(1.0f, 0.0f, 0.0f));
				const PerFrameData perFrameData = { .model = m, .mvp = p * m, .cameraPos = glm::vec4(0.0f) };

				skyProgram.useProgram();
				glNamedBufferSubData(perFrameDataBuffer, 0, kUniformBufferSize, &perFrameData);
				cube.BindVAO();
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			pWindow->HandleEventsIfAny();
		}

		
		free(sky);
		return 2;
	}
}