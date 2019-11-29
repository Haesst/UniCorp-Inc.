#include "Powerup.h"
#include "Config.h"
#include "SoundManager.h"
#include "Player.h"
#include "UI.h";

#include <SpriteManager.h>
#include <EntityManager.h>
#include <Collider.h>
#include <iostream>
#include <Vector2D.h>

Powerup::Powerup() {}

Powerup::~Powerup() {}

void Powerup::onCollision(Tag tagau)
{
	switch (tagau)
	{
		//case Tag::Enemyau: std::cout << "Enemy collided with Enemy" << std::endl ; break;
	case Tag::Playerau:
		std::cout << "Powerup collided with Player" << std::endl;
		// Todo: powerup effect
		PowerupEffect();
		break;
	}
}

void Powerup::PowerupEffect()
{
	std::cout << "POWERUP: This powerup has a dummy effect." << std::endl;
	//Player* player = dynamic_cast<Player*>(FG::EntityManager::Instance()->GetPlayer());
	//player->AddToScore(score); Maybe add score later on.
	//UI::Instance()->UpdateScore();

	//TODO: Find appropriate powerup sound.
	//SoundManager::Instance()->PlaySound("EnemyExplosion"); 
	
	Active = false;
}

Powerup::Powerup(FG::SpriteManager* spriteManagerRef, FG::Vector2D pos)
{
	position.x = pos.x;
	position.y = pos.y;

	Active = true;
	spriteManager = spriteManagerRef;

	sprite = spriteManager->CreateSprite("../TestingAssets/PowerUpBase.png", 1, 1, 32, 32);
	rect = { 0,0,32,32 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	rect = { (int)position.x, (int)position.y, 32, 32 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	myTagau = Tag::Powerupau;
}

void Powerup::Update(float deltaTime)
{
	SetPosition(FG::Vector2D(position.x, position.y + 3));
	rect = { (int)position.x, (int)position.y, 32, 32 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	UpdateCollider();
}

void Powerup::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}