#include "Game.h"
#include "../Common/IoC/Container.h"


namespace GNF::Core
{
	void Game::Init()
	{
		std::string str("Indie MC");
		GNF::SU::Windowing::WindowProps props(str, 640, 428, 0, 0);
		auto logger = GNF::Common::IoC::Container::GetInstance()->Resolve<GNF::SU::Logging::ILogger>();
		m_window.reset(new GNF::OpenGL::Windowing::OpenGL_Window(props, logger.get()));
		m_window->Init(SU::Windowing::GLFW);

	}
	void Game::Update()
	{
		UpdateStatistics();
		UpdateStates(m_statistics.GetDeltaTime());
	}
	void Game::Render()
	{
	}
	void Game::UpdateStatistics()
	{
		m_statistics.Reset();
		int fps = m_statistics.GetFPS();
		auto logger = GNF::Common::IoC::Container::GetInstance()->Resolve<GNF::SU::Logging::ILogger>();

		if (fps != -1)
		{
			logger->Info(std::format("FPS : [{}]",fps));
		}
	}
	void Game::UpdateStates(const float dt)
	{
		auto logger = GNF::Common::IoC::Container::GetInstance()->Resolve<GNF::SU::Logging::ILogger>();
		//logger->Info(std::format("DeltaTime : [{}]",dt));
	}
	void Game::Run()
	{
		m_statistics.Start();
		while (m_window->IsOpen())
		{
			m_window->ClearColor(0.f,1.f,1.f,1.f);

			m_window->ClearBufferBit();

			Update();

			Render();


			m_window->HandleEventsIfAny();
			m_window->SwapBuffers();
		}
	}
	Game::~Game()
	{
		int a = 5;
	}
}