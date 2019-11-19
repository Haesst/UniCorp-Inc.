#include "Player.h"
#include "PlayerState.h"

#include <SpriteManager.h>

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>

#include <Collider.h>

Player::Player(FG::InputManager* inputManager, FG::Camera* camera, FG::SpriteManager* spriteManagerRef) : inputManager(inputManager), camera(camera), spriteManager (spriteManagerRef)
{
	sprite = spriteManager->CreateSprite("../TestingAssets/FIREBALL.png", 1, 1, 900, 800);
	myCollider->square.w = 900;
	myCollider->square.h = 800;

	playerState = new PlayerState();
}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
	rect = {(int)position.x, (int)position.y, 900, 800 };

	playerState->Update(this, deltaTime);
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

void Player::SetPosition(FG::Vector2D position)
{
	this->position = position;
}

FG::Vector2D Player::GetPosition()
{
	return position;
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