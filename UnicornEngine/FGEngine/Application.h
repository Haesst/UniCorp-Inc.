#pragma once

namespace FG
{
	// Abstract class, we only have pure virtuals
	class Application
	{
	public:
		virtual ~Application() {}

		virtual bool Initialize() = 0; // ( = 0 equals Pure virtual) Initialize everything
		virtual void Run() = 0; // Will include game loop
		virtual void Shutdown() = 0; // Will clean everything up
	};

	Application* CreateApplication();
}