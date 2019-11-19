#pragma once

#include <string>
#include <Entity.h>
#include <Vector2D.h>

namespace FG
{
	class SpriteManager;
	class Camera;
}

class Enemy : public FG::Entity
{
public:
	Enemy(int param[4], const char filename[50], FG::SpriteManager* spriteManagerRef);
	~Enemy();

	virtual void Update(float deltaTime) override; //*?
	virtual void Render(FG::Camera* const camera) override;

private:
	Enemy();
	void MoveEnemy(float deltaTime);
	FG::Vector2D position;
	FG::SpriteManager* spriteManager;


	// Inherited via Entity
	virtual void onCollision(FG::Collider* theOtherCollider) override;

};