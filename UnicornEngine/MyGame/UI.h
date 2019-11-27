#pragma once

#include <Entity.h>
#include <SpriteManager.h>
#include <SDL_ttf.h>

namespace FG
{
	class Camera;
	class Sprite;
}
class Player;

class UI
{
private:
	FG::SpriteManager* spriteManager;
	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_Rect playerScoreRect;
	SDL_Surface* playerScoreSurface = nullptr;
	TTF_Font* scoreFont = nullptr;
	SDL_Texture* scoreTexture = nullptr;
	FG::Sprite* playerScoreSprite = nullptr;

	SDL_Rect pilotPortraitRect;
	FG::Sprite* pilotPortraitStage1 = nullptr;
	FG::Sprite* pilotPortraitStage2 = nullptr;
	FG::Sprite* pilotPortraitStage3 = nullptr;

	SDL_Rect heartRect;
	FG::Sprite* heart = nullptr;

	Player* player;


public:
	UI();
	~UI();

	void Update(float deltatime);
	void Render(FG::Camera* const camera);

	static UI* Instance();
	void Initialize(FG::SpriteManager* spriteManager, SDL_Renderer* renderer, SDL_Window* window);
	void UpdateScore();

private:
	void DrawPortrait();
	void DrawHearts();
	void DrawScore();
};