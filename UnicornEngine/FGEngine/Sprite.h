#pragma once
#include <SDL.h>

namespace FG
{
	class Sprite
	{
	public:
		Sprite(SDL_Texture* texture, int x, int y, int w, int h);
		~Sprite();
		SDL_Rect GetSource();
		SDL_Texture* GetTexture();
		void SetSource(int x, int y, int h, int w);

	protected:
		Sprite();
		SDL_Texture* myTexture;
		SDL_Rect Source;
	};
}
//sprite. an png(optimal), jpeg

//spriteManager

//gameObject