#pragma once

#include <Entity.h>
#include <Vector2D.h>

namespace FG
{
	class InputManager;
	class Camera;
	class SpriteManager;
}

class Player : public FG::Entity
{
public:
	Player(FG::InputManager* inputManager, FG::Camera* camera, FG::SpriteManager* spriteManagerRef);

	virtual void Update(float deltaTime) override;
	virtual void Render(FG::Camera* const camera) override;

private:
	Player() {}

	void MovePlayer(float deltaTime);
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;

	//FG::Vector2D position;
	FG::SpriteManager* spriteManager;


	// Inherited via Entity
	virtual void onCollision(Tag tagau) override;

};