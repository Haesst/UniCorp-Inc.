#include "InputManager.h"

#include <SDL_events.h>
#include <SDL_timer.h>

namespace FG
{

	void InputManager::Initialize()
	{
		keys = SDL_GetKeyboardState(nullptr);
		lastKeys = keys;
	}

	void InputManager::Update(bool& shouldQuit)
	{
		SDL_Event event;
		lastKeys = keys; // Set last frame keys to the current before updating
		keys = SDL_GetKeyboardState(nullptr); // Get the new keys

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEMOTION:
				mousePosition.x = (float)event.motion.x;
				mousePosition.y = (float)event.motion.y;
				mouseMovement.x = (float)event.motion.xrel;
				mouseMovement.y = (float)event.motion.yrel;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseButtons[event.button.button] = true;
				mouseButtonTimes[event.button.button] = SDL_GetTicks();
				break;
			case SDL_MOUSEBUTTONUP:
				mouseButtons[event.button.button] = false;
				mouseButtonTimes[event.button.button] = 0;
				break;
			case SDL_QUIT:
				shouldQuit = true;
				break;
			}
		}
	}

	bool InputManager::IsKeyPressed(SDL_Scancode key) const
	{
		return !lastKeys[key] && keys[key];
	}

	bool InputManager::IsKeyReleased(SDL_Scancode key) const
	{
		return lastKeys[key] && !keys[key];
	}

	float InputManager::ElapsedKeyTime(SDL_Scancode key) const
	{
		return (SDL_GetTicks() - keyTimes[key]) * 0.001f;
	}

	bool InputManager::IsMouseButtonPressed(unsigned int mouseButton) const
	{
		return !lastMouseButtons[mouseButton] && mouseButtons[mouseButton];
	}

	bool InputManager::IsMouseButtonReleased(unsigned int mouseButton) const
	{
		return lastMouseButtons[mouseButton] && mouseButtons[mouseButton];
	}

	float InputManager::ElapsedMouseButtonTime(unsigned int mouseButton) const
	{
		return (SDL_GetTicks() - mouseButtonTimes[mouseButton]) * 0.001f;
	}

}