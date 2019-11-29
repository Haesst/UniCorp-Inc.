#include "PowerupMultiSpread.h"
#include "Config.h"
#include "SoundManager.h"
#include "Player.h"
#include "UI.h";

#include <SpriteManager.h>
#include <EntityManager.h>
#include <Collider.h>
#include <iostream>
#include <Vector2D.h>

PowerupMultiSpread::PowerupMultiSpread() {}

PowerupMultiSpread::~PowerupMultiSpread() {}

void PowerupMultiSpread::onCollision(Tag tagau)
{
	switch (tagau)
	{
	case Tag::Playerau:
		std::cout << "Powerup collided with Player" << std::endl;
		PowerupEffect();
		break;
	}
}

void PowerupMultiSpread::PowerupEffect()
{
	std::cout << "M-M-MULTISPREAD!!!" << std::endl;
	Player* player = dynamic_cast<Player*>(FG::EntityManager::Instance()->GetPlayer());
	player->activePowerup = true;
	player->currentPowerup = "Multispread";
	player->powerupDuration = 10.0f;
	player->AddToScore(score);

	//TODO: Find appropriate powerup sound.
	SoundManager::Instance()->PlaySound("Powerup"); 

	Active = false;
}

PowerupMultiSpread::PowerupMultiSpread(FG::SpriteManager* spriteManagerRef, FG::Vector2D pos)
{
	position.x = pos.x;
	position.y = pos.y;

	Active = true;
	spriteManager = spriteManagerRef;

	sprite = spriteManager->CreateSprite("../TestingAssets/PowerUpMultiSpread.png", 1, 1, 32, 32);
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

void PowerupMultiSpread::Update(float deltaTime)
{
	SetPosition(FG::Vector2D(position.x, position.y + 3));
	rect = { (int)position.x, (int)position.y, 32, 32 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	UpdateCollider();
}

void PowerupMultiSpread::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}