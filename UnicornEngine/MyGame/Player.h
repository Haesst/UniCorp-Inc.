#pragma once

#include <Entity.h>
#include <Vector2D.h>
#include <Sprite.h>

namespace FG
{
	class InputManager;
	class Camera;
	class Sprite;
	class SpriteManager;
}

class Player : public FG::Entity, public FG::Sprite
{
public:
	Player(FG::InputManager* inputManager, FG::Camera* camera, FG::SpriteManager* spriteManagerRef);

	virtual void Update(float deltaTime) override;
	virtual void Render(FG::Camera* const camera) override;
	FG::Sprite* sprite = nullptr;
	SDL_Rect rect;


private:
	Player() {}

	void MovePlayer(float deltaTime);
private:
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;

	FG::Vector2D position;
	FG::SpriteManager* spriteManager;

	float playerSpeed = 250.0f;

};