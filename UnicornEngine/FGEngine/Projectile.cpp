#include "Projectile.h"
#include <Vector2D.h>
#include <Camera.h>
#include <iostream>
#include <Collider.h>

Projectile::Projectile(FG::Vector2D position, FG::Vector2D direction)
	: position(position), direction(direction)
{}

void Projectile::Update(float deltaTime)
{
	std::cout << position.x << std::endl;
	position = direction * speed * deltaTime;
}

void Projectile::Render(FG::Camera* const camera)
{
	//
}

void Projectile::onCollision(FG::Collider* theOtherCollider)
{
	//
}
