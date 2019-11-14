#pragma once
#include "Entity.h"
#include <Vector2D.h>

namespace FG
{
	class Camera;
	class Collider;
}

class Projectile : public FG::Entity
{
private:
	FG::Vector2D position;
	FG::Vector2D direction;

protected:
	float lifeTime = 5.0f;
	float speed = 300.0f;

public:
	Projectile(FG::Vector2D position, FG::Vector2D direction);

	virtual void Update(float deltaTime) override;
	virtual void Render(FG::Camera* const camera) override;


	void onCollision(FG::Collider* theOtherCollider) override;

};