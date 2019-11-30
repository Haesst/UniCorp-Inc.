#include "Player.h"
#include "PlayerState.h"
#include "Projectile.h"
#include "UI.h"

#include <SpriteManager.h>
#include <InputManager.h>
#include <Camera.h>
#include <Collider.h>
#include <EntityManager.h>
#include "SoundManager.h"

#include <iostream>
#include <memory>
#include <SDL_render.h>

Player::Player(FG::InputManager* inputManager, FG::Camera* camera, FG::SpriteManager* spriteManagerRef) : inputManager(inputManager), camera(camera), spriteManager (spriteManagerRef)
{
	score = 0;
	defeatedBosses = 0;
	playerState = new PlayerState();
	playerState->Configure(this);
	playerState->ChangeState(new PlayerState::Idle());
	sprite = spriteManager->CreateSprite("../TestingAssets/player.png", 1, 1, 33, 40);
	rect = { 0,0, 33, 40 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;

	myTagau = Tag::Playerau;
}

void Player::Update(float deltaTime)
{
	if (immortalCounter > 0.0f)
	{
		immortalCounter -= deltaTime;
	}

	if (immortal)
	{
		if (immortalFlashCounter < 1.1f)
		{
			immortalFlashCounter += deltaTime;
		}
		else if (immortalFlashCounter > 0.9f)
		{
			immortalFlashCounter -= deltaTime;
		}
	}

	if (immortal && immortalCounter <= 0.0f)
	{
		immortal = false;
	}

	if (currentPowerup == "MoveSpeed")
	{ SetMoveSpeed(500.0f); }
	else
	{ SetMoveSpeed(defaultMoveSpeed); }
	if (currentPowerup == "AttackSpeed")
	{ SetAttackSpeed(0.15f); }
	else
	{ SetAttackSpeed(defaultAttackSpeed); }
	MovePlayer(deltaTime);

	if (activePowerup == true && powerupDuration > 0.0f) { powerupDuration -= deltaTime; }
	if (activePowerup == true && powerupDuration <= 0.0f)
	{
		if (currentPowerup == "MoveSpeed")
		{
			SetMoveSpeed(defaultMoveSpeed);
		}
		if (currentPowerup == "MoveSpeed")
		{
			SetAttackSpeed(defaultAttackSpeed);
		}
		activePowerup = false;
		currentPowerup = "";
		std::cout << "Your powerup has expired..." << std::endl;
	}

	if (currentShotTimer > 0.0f)
	{
		currentShotTimer -= deltaTime;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_SPACE) && currentShotTimer <= 0.0f)
	{
		if (activePowerup == true)
		{
			if (currentPowerup == "Spread")
			{
				Projectile* projectile = new Projectile(FG::Vector2D(0, -1), FG::Vector2D(position.x + 15.0f, position.y - 60.0f), spriteManager, Projectile::BulletType::PlayerBullet);
				Projectile* projectile2 = new Projectile(FG::Vector2D(0, -1), FG::Vector2D(position.x, position.y - 60.0f), spriteManager, Projectile::BulletType::PlayerBullet);
				Projectile* projectile3 = new Projectile(FG::Vector2D(0, -1), FG::Vector2D(position.x + 30.0f, position.y - 60.0f), spriteManager, Projectile::BulletType::PlayerBullet);
				projectile->Active = true, projectile2->Active = true, projectile3->Active = true;
				FG::EntityManager::Instance()->AddEntity(projectile, "Projectile");
				FG::EntityManager::Instance()->AddEntity(projectile2, "Projectile");
				FG::EntityManager::Instance()->AddEntity(projectile3, "Projectile");
			}
			else if (currentPowerup == "Multispread" || currentPowerup == "Ringshot")
			{
				Projectile* projectile = new Projectile(FG::Vector2D(-1, -1), FG::Vector2D(position.x - 6.0f, position.y - 20.0f), spriteManager, Projectile::BulletType::PlayerBigBullet);
				Projectile* projectile2 = new Projectile(FG::Vector2D(0, -1), FG::Vector2D(position.x + 9.0f, position.y - 20.0f), spriteManager, Projectile::BulletType::PlayerBigBullet);
				Projectile* projectile3 = new Projectile(FG::Vector2D(1, -1), FG::Vector2D(position.x + 24.0f, position.y - 20.0f), spriteManager, Projectile::BulletType::PlayerBigBullet);
				Projectile* projectile4 = new Projectile(FG::Vector2D(-1, 1), FG::Vector2D(position.x - 6.0f, position.y + 36.0f), spriteManager, Projectile::BulletType::PlayerBigBullet);
				Projectile* projectile5 = new Projectile(FG::Vector2D(0, 1), FG::Vector2D(position.x + 9.0f, position.y + 36.0f), spriteManager, Projectile::BulletType::PlayerBigBullet);
				Projectile* projectile6 = new Projectile(FG::Vector2D(1, 1), FG::Vector2D(position.x + 24.0f, position.y + 36.0f), spriteManager, Projectile::BulletType::PlayerBigBullet);
				projectile->Active = true, projectile2->Active = true, projectile3->Active = true;
				projectile4->Active = true, projectile5->Active = true, projectile6->Active = true;
				FG::EntityManager::Instance()->AddEntity(projectile, "Projectile");
				FG::EntityManager::Instance()->AddEntity(projectile2, "Projectile");
				FG::EntityManager::Instance()->AddEntity(projectile3, "Projectile");
				FG::EntityManager::Instance()->AddEntity(projectile4, "Projectile");
				FG::EntityManager::Instance()->AddEntity(projectile5, "Projectile");
				FG::EntityManager::Instance()->AddEntity(projectile6, "Projectile");
			} //todo: Ringshot needs it's own effect.
			/*else if (currentPowerup == "Ringshot")
			{
				Projectile* projectile = new Projectile(FG::Vector2D(0, -1), FG::Vector2D(position.x + 15.0f, position.y - 60.0f), spriteManager, Projectile::BulletType::PlayerBullet);
				projectile->Active = true;
				FG::EntityManager::Instance()->AddEntity(projectile, "Projectile");
			}*/
			else
			{
				Projectile* projectile = new Projectile(FG::Vector2D(0, -1), FG::Vector2D(position.x + 15.0f, position.y - 60.0f), spriteManager, Projectile::BulletType::PlayerBullet);
				projectile->Active = true;
				FG::EntityManager::Instance()->AddEntity(projectile, "Projectile");
				SoundManager::Instance()->PlaySound("PlayerShot");
				currentShotTimer = timeBetweenShots;
			}
			SoundManager::Instance()->PlaySound("PlayerShot");
			currentShotTimer = timeBetweenShots;
		}
		else
		{
			Projectile* projectile = new Projectile(FG::Vector2D(0, -1), FG::Vector2D(position.x + 15.0f, position.y - 60.0f), spriteManager, Projectile::BulletType::PlayerBullet);
			projectile->Active = true;
			FG::EntityManager::Instance()->AddEntity(projectile, "Projectile");
			SoundManager::Instance()->PlaySound("PlayerShot");
			currentShotTimer = timeBetweenShots;
		}
	}

	FG::Vector2D temppos = { 0, 0 };
	if (inputManager->IsKeyDown(SDL_SCANCODE_RCTRL))
	{
		FG::EntityManager::Instance()->AddEntity("Enemy", temppos);
	}

	rect = {(int)position.x, (int)position.y, 33, 40 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	myCollider->square.w = 33;
	myCollider->square.h = 40;
	UpdateCollider();
	playerState->Update();
	
}

void Player::Render(FG::Camera* const camera)
{
	/*SDL_Color oldDrawColor;
	SDL_Color color{ 0, 0, 255, 255 };

	SDL_GetRenderDrawColor(camera->GetInternalRenderer(), &oldDrawColor.r, &oldDrawColor.g, &oldDrawColor.b, &oldDrawColor.a);
	SDL_SetRenderDrawColor(camera->GetInternalRenderer(), color.r, color.g, color.b, color.a);

	SDL_Rect finalRect{ (int)position.x, (int)position.y, 50,50 };
	SDL_RenderFillRect(camera->GetInternalRenderer(), &finalRect);

	SDL_SetRenderDrawColor(camera->GetInternalRenderer(), oldDrawColor.r, oldDrawColor.g, oldDrawColor.b, oldDrawColor.a);*/
	
	if (immortal)
	{
		if (immortalFlashCounter < 1.0f)
		{
			std::cout << "flash alpha" << std::endl;
			spriteManager->Draw(sprite, rect, { 255,255,255 }, 100);
		} 
		else
		{
			std::cout << "flash red" << std::endl;
			spriteManager->Draw(sprite, rect, { 255,0,0 }, 255);
		}
	}
	else
	{
		spriteManager->Draw(sprite, rect, { 255,255,255 }, 255);
	}
	spriteManager->DebugDraw(myCollider->square);
}

void Player::AddToScore(int score)
{
	this->score += score;
	UI::Instance()->UpdateScore();
}

void Player::DefeatedBoss()
{
	this->defeatedBosses += 1;
}


void Player::MovePlayer(float deltaTime)
{
	FG::Vector2D movement;

	if (inputManager->IsKeyDown(SDL_SCANCODE_A))
	{
		movement.x -= 1.0f;
	}
	else if (inputManager->IsKeyDown(SDL_SCANCODE_D))
	{
		movement.x += 1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_W))
	{
		movement.y -= 1.0f;
	}
	else if (inputManager->IsKeyDown(SDL_SCANCODE_S))
	{
		movement.y += 1.0f;
	}

	FG::Vector2D newPosition = position;

	if (movement.x != 0 || movement.y != 0)
	{
		newPosition = position + (movement.Normalized() * movementSpeed * deltaTime);
	}
	// Todo: Remove magic numbers and define screen size somewhere

	int height;
	int width;

	SDL_GetWindowSize(camera->GetWindow()->GetInternalWindow(), &width, &height);

	if (newPosition.x < 0)
	{
		newPosition.x = 0;
	}
	else if (newPosition.x > width - rect.w)
	{
		newPosition.x = width - rect.w;
	}

	if (newPosition.y < 0)
	{
		newPosition.y = 0;
	}
	else if (newPosition.y > height - rect.h - 100)
	{
		newPosition.y = height - rect.h - 100;
	}

	position = newPosition;
}

void Player::onCollision(Tag tagau)
{
		switch (tagau)
		{
		case EnemyBulletau:
			if (!immortal)
			{
				lifes--;
				SoundManager::Instance()->PlaySound("PlayerDamage");
				immortal = true;
				immortalCounter = immortalTime;
			}
		}
}