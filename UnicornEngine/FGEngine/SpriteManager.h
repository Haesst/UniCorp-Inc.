#pragma once

#include "Window.h"
class Sprite;

namespace FG
{
	class SpriteManager
	{
	public:
		virtual ~SpriteManager() {}
		bool Initialize(SDL_Window* windowRef);
		void Draw(Sprite* sprite);
		void Shutdown();

		SDL_Window* window = nullptr;

	private:


	};
}

