#include "Player.h"

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>

Player::Player(FG::InputManager* inputManager, FG::Camera* camera) : inputManager(inputManager), camera(camera)
{}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
}

void Player::Render(FG::Camera* const camera)
{
	SDL_Color oldDrawColor;
	SDL_Color color{ 0, 0, 255, 255 };

	SDL_GetRenderDrawColor(camera->GetInternalRenderer(), &oldDrawColor.r, &oldDrawColor.g, &oldDrawColor.b, &oldDrawColor.a);
	SDL_SetRenderDrawColor(camera->GetInternalRenderer(), color.r, color.g, color.b, color.a);

	SDL_Rect finalRect{ (int)position.x, (int)position.y, 50,50 };
	SDL_RenderFillRect(camera->GetInternalRenderer(), &finalRect);

	SDL_SetRenderDrawColor(camera->GetInternalRenderer(), oldDrawColor.r, oldDrawColor.g, oldDrawColor.b, oldDrawColor.a);
}

void Player::MovePlayer(float deltaTime)
{
	FG::Vector2D movement;

	if (inputManager->IsKeyDown(SDL_SCANCODE_A))
	{
		movement.x -= 1.0f;
	}
	if (inputManager->IsKeyDown(SDL_SCANCODE_D))
	{
		movement.x += 1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_W))
	{
		movement.y -= 1.0f;
	}
	if (inputManager->IsKeyDown(SDL_SCANCODE_S))
	{
		movement.y += 1.0f;
	}

	position += movement * playerSpeed * deltaTime;
}