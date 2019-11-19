#include "Enemy.h"
#include <string>
#include <SpriteManager.h>
#include <Collider.h>

Enemy::Enemy(){}

bool move_right = true;
bool move_down = true;

void Enemy::onCollision(FG::Collider* theOtherCollider)
{
}

Enemy::Enemy(int enemy_spawn[4], const char filename[50], FG::SpriteManager* spriteManagerRef) : spriteManager(spriteManagerRef)
{
	std::string folder = "../TestingAssets/";

	movementSpeed = 100.0f;

	folder.append(filename);
	char filepath[1024];
	strcpy_s(filepath, folder.c_str());

	sprite = spriteManager->CreateSprite(filepath, 1, 1, 900, 800);
	rect = { enemy_spawn[0], enemy_spawn[1] , enemy_spawn[2] , enemy_spawn[3]};
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	position.x = rect.x;
	position.y = rect.y;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	Enemy::MoveEnemy(deltaTime);
	rect = { (int)position.x, (int)position.y, 90, 80 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	UpdateCollider();
}

void Enemy::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}

void Enemy::MoveEnemy(float deltaTime)
{
	FG::Vector2D movement;
	
	if (position.x >= 935)
	{ move_right = false; }
	else if	(position.x <= 5)
	{ move_right = true; }

	if (move_right)
	{
		movement.x += 1.5f;
	}
	else
	{
		movement.x -= 1.5f;
	}

	if (position.y >= 680)
	{ move_down = false; }
	else if (position.y <= 5)
	{ move_down = true;	}

	if (move_down)
	{
		movement.y += 1.0f;
	}
	else
	{
		movement.y -= 1.0f;
	}

	position += movement * movementSpeed * deltaTime;
}
