#pragma once

#include <string>
#include <Entity.h>
#include <Vector2D.h>

namespace FG
{
	class SpriteManager;
	class Camera;
}

class PowerupMoveSpeed : public FG::Entity
{
public:
	PowerupMoveSpeed();
	PowerupMoveSpeed(FG::SpriteManager* spriteManagerRef, FG::Vector2D position);
	~PowerupMoveSpeed();

	virtual void Update(float deltaTime) override; //*?
	virtual void Render(FG::Camera* const camera) override;

private:
	void PowerupEffect();
	void MovePowerup(float deltaTime);
	virtual void onCollision(Tag tagau) override;
	FG::SpriteManager* spriteManager;
	int score = 15;
};

