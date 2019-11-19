#pragma once

#include <Entity.h>
#include <Vector2D.h>

namespace FG
{
	class InputManager;
	class Camera;
	class SpriteManager;
}

class PlayerState;

class Player : public FG::Entity
{
public:
	Player(FG::InputManager* inputManager, FG::Camera* camera, FG::SpriteManager* spriteManagerRef);

	virtual void Update(float deltaTime) override;
	virtual void Render(FG::Camera* const camera) override;
	virtual void SetPosition(FG::Vector2D position) override;
	virtual FG::Vector2D GetPosition() override;

	FG::Sprite* sprite = nullptr;
	SDL_Rect rect;


private:
	Player() {}

	void MovePlayer(float deltaTime);

	PlayerState* playerState;

private:
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;

	FG::Vector2D position;
	FG::SpriteManager* spriteManager;

	float playerSpeed = 250.0f;

};