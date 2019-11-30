#pragma once

#include "Window.h"
#include <vector>
#include <map>


namespace FG
{
	class Sprite;
	class SpriteManager
	{
	public:
		//bool Initialize(struct SDL_Window* windowRef);
		bool Initialize(SDL_Window* windowRef, SDL_Renderer* rendererRef);
	
		void Shutdown();
		Sprite* CreateSprite(const char* file, int x, int y, int w, int h);
		SpriteManager() {}
		~SpriteManager() {}
		void Clear();
		void Present();
		void Draw(Sprite* sprite, SDL_Rect rect);
		void Draw(Sprite* sprite, SDL_Rect rect, SDL_Color colorModifier);
		void Draw(Sprite* sprite, SDL_Rect rect, float alpha);
		void Draw(Sprite* sprite, SDL_Rect rect, SDL_Color colorModifier, float alpha);
		void DebugDraw(SDL_Rect debugrect);

		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		
	private:
		
		std::map<std::string, SDL_Texture*>textures;
		std::vector<Sprite*>sprites;

	};
}

