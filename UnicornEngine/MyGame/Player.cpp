#include "Player.h"
#include <SpriteManager.h>

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>

#include <Collider.h>

Player::Player(FG::InputManager* inputManager, FG::Camera* camera, FG::SpriteManager* spriteManagerRef) : inputManager(inputManager), camera(camera), spriteManager (spriteManagerRef)
{
	sprite = spriteManager->CreateSprite("../TestingAssets/FROGGY.png", 1, 1, 92, 98);
	rect = { 0,0, 92, 98 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
	rect = {(int)position.x, (int)position.y, 92, 98 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	UpdateCollider();
	
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

void Player::onCollision(FG::Collider* theOtherCollider)
{
}
