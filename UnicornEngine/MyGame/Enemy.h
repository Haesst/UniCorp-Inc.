#pragma once

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
	Enemy(FG::SpriteManager* spriteManagerRef);
	~Enemy();

	virtual void Update(float deltaTime) override; //*?
	virtual void Render(FG::Camera* const camera) override;

private:
	Enemy();
	FG::SpriteManager* spriteManager;


	// Inherited via Entity
	virtual void onCollision(FG::Collider* theOtherCollider) override;

};