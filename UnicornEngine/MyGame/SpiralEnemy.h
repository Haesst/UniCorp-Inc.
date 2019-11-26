#pragma once
#include "Enemy.h"
#include <Vector2D.h>

namespace FG
{
	class SpriteManager;
	class Camera;
}

class SpiralEnemy : public Enemy
{
public:
	SpiralEnemy();
	SpiralEnemy(FG::SpriteManager* spriteManagerRef, FG::Vector2D* direction);
	~SpiralEnemy();

	virtual void Update(float deltaTime) override; //*?
	virtual void Render(FG::Camera* const camera) override;


private:
	virtual void onCollision(Tag tagau) override;
	void EnemyDies();
	FG::Vector2D* direction;
	FG::SpriteManager* spriteManager;
	float speed = 3;
};
