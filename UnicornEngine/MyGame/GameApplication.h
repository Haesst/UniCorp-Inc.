#pragma once

#include <Application.h>

namespace FG
{
	class SpriteManager;
	class Window;
}

class GameApplication : public FG::Application
{
public:
	virtual bool Initialize() override;
	virtual void Run() override;
	virtual void Shutdown() override;
private:
	FG::Window* window = nullptr;
	FG::SpriteManager* spriteManager = nullptr;
};

FG::Application* FG::CreateApplication()
{
	return new GameApplication();
}