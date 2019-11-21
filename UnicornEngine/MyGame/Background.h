#pragma once

#include <Entity.h>
#include <SpriteManager.h>

namespace FG
{
	class Camera;
}

class Background : public FG::Entity
{
private:
	FG::SpriteManager* spriteManager;
	SDL_Rect secondImage;

	float speed;

public:

	Background(const char* path, FG::SpriteManager* spriteManager, float speed);
	~Background();

	void Update(float deltaTime) override;
	void Render(FG::Camera* const camera) override;

	// Inherited via Entity
	virtual void onCollision(Tag tagau) override {return;};

};