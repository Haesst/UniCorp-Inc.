#include "Player.h"
#include "PlayerState.h"
#include "Projectile.h"

#include <SpriteManager.h>
#include <InputManager.h>
#include <Camera.h>
#include <Collider.h>
#include <EntityManager.h>

#include <iostream>
#include <memory>
#include <SDL_render.h>


Player::Player(FG::InputManager* inputManager, FG::Camera* camera, FG::SpriteManager* spriteManagerRef, FG::EntityManager* entityManager) : inputManager(inputManager), camera(camera), spriteManager (spriteManagerRef), entityManager(entityManager)
{
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
		Projectile* projectile = new Projectile(FG::Vector2D(0, -1), spriteManager);
		projectile->SetPosition(position + FG::Vector2D(20, -60));
		projectile->Active = true;
		entityManager->AddEntity(projectile, "Projectile");
		currentShotTimer = timeBetweenShots;
	}

	rect = {(int)position.x, (int)position.y, 33, 40 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
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

	position += movement * movementSpeed * deltaTime;
}

void Player::onCollision(Tag tagau)
{
		switch (tagau)
		{
		case Tag::Playerau: std::cout << "Player collided with Enemy" << std::endl; break;
		//case Tag::Enemyau: std::cout << "Enemy collided" << std::endl; break;
		
		}
	
}