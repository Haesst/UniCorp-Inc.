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
public:
	SDL_Rect highscoreTextRect;
	SDL_Surface* highscoreSurface = nullptr;
	SDL_Texture* highscoreTexture = nullptr;
	FG::Sprite* highscoreSprite = nullptr;
private:
	FG::SpriteManager* spriteManager;
	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_Rect playerScoreRect;
	TTF_Font* scoreFont = nullptr;
	SDL_Surface* playerScoreSurface = nullptr;
	SDL_Texture* scoreTexture = nullptr;
	FG::Sprite* playerScoreSprite = nullptr;

	SDL_Rect pilotPortraitRect;
	FG::Sprite* pilotPortraitStage1 = nullptr;
	FG::Sprite* pilotPortraitStage2 = nullptr;
	FG::Sprite* pilotPortraitStage3 = nullptr;

	SDL_Rect heartRect;
	FG::Sprite* heart = nullptr;

	SDL_Rect highscoreRect;
	FG::Sprite* highscoreWindow = nullptr;

	Player* player;
public:
	UI();
	~UI();

	void Update(float deltatime);
	void Render(FG::Camera* const camera);

	static UI* Instance();
	void Initialize(FG::SpriteManager* spriteManager, SDL_Renderer* renderer, SDL_Window* window);
	void UpdateScore();
	void ResetUI();

	SDL_Rect DrawHighscoreWindow();
	void LowerHighscoreWindow(SDL_Rect highscoreRect);
	void DrawHighscores(std::string line, int w, int h);

private:
	void DrawPortrait();
	void DrawHearts();
	void DrawScore();
};