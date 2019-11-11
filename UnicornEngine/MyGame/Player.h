#pragma once

#include <Entity.h>
#include <Vector2D.h>

namespace FG
{
	class InputManager;
	class Camera;
}

class Player : public FG::Entity
{
public:
	Player(FG::InputManager* inputManager, FG::Camera* camera);

	virtual void Update(float deltaTime) override;
	virtual void Render(FG::Camera* const camera) override;

private:
	Player() {}

	void MovePlayer(float deltaTime);
private:
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;

	FG::Vector2D position;

	float playerSpeed = 250.0f;

};