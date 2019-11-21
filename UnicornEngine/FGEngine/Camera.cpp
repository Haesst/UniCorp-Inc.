#include "Camera.h"

#include "Logger.h"
#include "Window.h"

#include <SDL_render.h>

#include <cassert>

namespace FG
{
	bool Camera::Initialize(Window* window)
	{
		// Make sure we have a window before setting owner window
		assert(window);

		ownerWindow = window;
		renderer = SDL_CreateRenderer(window->GetInternalWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (!renderer)
		{
			Logger::Log(SDL_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
			return false;
		}

		return true;
	}
	void Camera::Shutdown()
	{
		if (renderer)
		{
			SDL_DestroyRenderer(renderer);
			renderer = nullptr;
		}
	}
	void Camera::StartRenderFrame()
	{
		SDL_RenderClear(renderer);

	}
	void Camera::EndRenderFrame()
	{
		SDL_RenderPresent(renderer);
	}
	void Camera::SetColor(const SDL_Color& color)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	}
	SDL_Color Camera::GetColor()
	{
		Uint8 red = 0;
		Uint8 green = 0;
		Uint8 blue = 0;
		Uint8 alpha = 0;

		SDL_GetRenderDrawColor(renderer, &red, &green, &blue, &alpha);
		return { red, green, blue, alpha };
	}
}