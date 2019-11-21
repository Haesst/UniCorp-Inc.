#include "Background.h"

#include <Camera.h>
#include <iostream>

Background::Background(const char* path, FG::SpriteManager* spriteManager, float speed)
	: spriteManager(spriteManager), speed(speed)
{
	Active = true;
	sprite = spriteManager->CreateSprite(path, 0, 0, 480, 1600);
	rect = { 0, 0, 600, 1600 };
	secondImage = { 0, 1600, 600, 1600 };
	position = FG::Vector2D(0, 0);
}

Background::~Background()
{
}

void Background::Update(float deltaTime)
{
	position += FG::Vector2D(0, 1) * speed;
	if (position.y >= 1600.0f)
	{
		position.y = 0.0f;
		std::cout << "Looping image" << std::endl;
	}
	rect = { (int)position.x, (int)position.y, 600, 1600 };
	secondImage = { (int)position.x, (int)position.y - 1600, 600, 1600 };
}

void Background::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->Draw(sprite, secondImage);
}
