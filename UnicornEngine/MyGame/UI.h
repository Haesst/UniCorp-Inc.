#pragma once

#include <Entity.h>
#include <SpriteManager.h>

namespace FG
{
	class Camera;
}


class UI : public FG::Entity
{
private:
	FG::SpriteManager* spriteManager;

	SDL_Rect pilotPortraitRect;
	FG::Sprite* pilotPortraitStage1 = nullptr;
	FG::Sprite* pilotPortraitStage2 = nullptr;
	FG::Sprite* pilotPortraitStage3 = nullptr;

	SDL_Rect heartRect;
	FG::Sprite* heart = nullptr;

public:
	UI(const char* element, FG::SpriteManager* spritemanager);
	~UI();

	void Update(float deltatime) override;
	void Render(FG::Camera* const camera) override;

	virtual void onCollision(Tag tagau) override { return; };

private:
	void UpdateScore(float deltaTime);
	void DrawPortrait();
	void DrawHearts();
};