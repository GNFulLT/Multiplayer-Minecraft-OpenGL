#include <GLFW/glfw3.h>
#include <iostream>
#include "Common/IoC/Container.h"

#define GLFW_INCLUDE_NONE 



#include "Core/Game.h"
using namespace GNF::Common::IoC;


#ifdef _DEBUG
#ifndef DEBUG_NEW_MC
#define DEBUG_NEW_MC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
#pragma comment(linker, "/subsystem:console")
#pragma comment(lib,"mc_shared_utils_d.lib")
#pragma comment(lib,"opengl_utils_d.lib")

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    auto c = Container::Build();
    c->RegisterSingleton<GNF::SU::Logging::ILogger>(std::function<std::shared_ptr<GNF::SU::Logging::ILogger>()>([]() {return std::shared_ptr<GNF::SU::Logging::ILogger>(new GNF::SU::Logging::Logger()); }));
    
    auto logger = c->Resolve<GNF::SU::Logging::ILogger>();
    logger.get()->Info("Program Has Started");

    auto game = GNF::Core::Game::Build();
    game->Init();
    game->Run();

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    return 0;
   
}

#else

#pragma comment( linker, "/subsystem:windows" )
#pragma comment(lib,"mc_shared_utils.lib")
#pragma comment(lib,"opengl_utils.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    auto c = Container::Build();
    c.RegisterSingleton<ILogger>(std::function<std::shared_ptr<ILogger>()>([]() {return std::shared_ptr<ILogger>(new Logger()); }));

    auto logger = c.Resolve<ILogger>();
    logger.get()->Info("Program Has Started");
}


#endif

