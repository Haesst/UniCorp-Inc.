#pragma once

#include <string>
#include <Entity.h>
#include <Vector2D.h>

namespace FG
{
	class SpriteManager;
	class Camera;
}

class PowerupMultiSpread : public FG::Entity
{
public:
	PowerupMultiSpread();
	PowerupMultiSpread(FG::SpriteManager* spriteManagerRef, FG::Vector2D position);
	~PowerupMultiSpread();

	virtual void Update(float deltaTime) override; //*?
	virtual void Render(FG::Camera* const camera) override;

private:
	void PowerupEffect();
	void MovePowerup(float deltaTime);
	virtual void onCollision(Tag tagau) override;
	FG::SpriteManager* spriteManager;
	int score = 15;
};

