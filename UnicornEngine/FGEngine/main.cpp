#include "Application.h"
#include "Logger.h"

#include <cassert>
#include <SDL_main.h>

// Forward declare the CreateApplication since we're going to use it externally
extern FG::Application* FG::CreateApplication();

int main(int argc, char* argv[])
{
	// Hook up SDLs logger with our logger
	SDL_LogSetOutputFunction(&FG::Logger::LogSDL, nullptr);
	
	// Tell SDL that main is ready
	SDL_SetMainReady();

	// Create an application
	FG::Application* application = FG::CreateApplication();
	assert(application);

	// Try to initialize
	if (!application->Initialize())
	{
		// Initialization failed, clean up, delete and return -1
		application->Shutdown();
		delete application;
		return -1;
	}

	// Entering the game loop
	application->Run();

	// Clean everything up
	application->Shutdown();

	// Delete the application
	delete application;

	return 0;
}