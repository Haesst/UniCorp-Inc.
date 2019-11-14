#include "Player.h"
#include <SpriteManager.h>
#include <InputManager.h>
#include <EntityManager.h>

#include <Projectile.h>

#include <Camera.h>
#include <SDL_render.h>
#include <Collider.h>

// remove \/
#include <iostream>

Player::Player(FG::InputManager* inputManager, FG::Camera* camera, FG::SpriteManager* spriteManagerRef, FG::EntityManager* entityManager) : inputManager(inputManager), camera(camera), spriteManager (spriteManagerRef), entityManager(entityManager)
{
	sprite = spriteManager->CreateSprite("../TestingAssets/FIREBALL.png", 1, 1, 900, 800);
	myCollider->square.w = 900;
	myCollider->square.h = 800;
	rect = { (int)position.x, (int)position.y, 900, 800 };
}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);

	if (inputManager->IsKeyReleased(SDL_SCANCODE_SPACE))
	{
		std::cout << "Pew pew" << std::endl;
		Projectile* bullet = new Projectile(FG::Vector2D(250.0f, 270.0f), FG::Vector2D(0.f, -1.0f));
		if (bullet != nullptr)
		{
			entityManager->AddEntity(bullet);
		}
	}

	rect = {(int)position.x, (int)position.y, 900, 800 };
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

	position += movement * playerSpeed * deltaTime;
}