#pragma once

#include <SDL.h>

namespace FG
{
	class Collider
	{
	public:
		Collider();
		virtual ~Collider();

		SDL_Rect square;
		struct collider // a class that is always public by default
		{
			int top = 0;
			int bottom = 0;
			int left = 0;
			int right = 0;
		}; 
		collider bounds; //boundaries

	};
}