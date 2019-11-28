#include "Player.h"
#include "PlayerState.h"
#include "Projectile.h"

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
	MovePlayer(deltaTime);

	if (currentShotTimer > 0.0f)
	{
		currentShotTimer -= deltaTime;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_SPACE) && currentShotTimer <= 0.0f)
	{
		Projectile* projectile = new Projectile(FG::Vector2D(0, -1), FG::Vector2D(position.x + 15.0f, position.y - 60.0f), spriteManager, Projectile::BulletType::PlayerBullet);
		projectile->Active = true;
		FG::EntityManager::Instance()->AddEntity(projectile, "Projectile");
		SoundManager::Instance()->PlaySound("PlayerShot");
		currentShotTimer = timeBetweenShots;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_RCTRL))
	{
		FG::EntityManager::Instance()->AddEntity("Enemy", position);
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
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}

void Player::AddToScore(int score)
{
	this->score += score;
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
			lifes--;
		}
}