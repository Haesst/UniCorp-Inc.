#include "UI.h"

#include <SpriteManager.h>

UI::UI(const char* element, FG::SpriteManager* spriteManager) : spriteManager(spriteManager)
{
	Active = true;
	sprite = spriteManager->CreateSprite("../TestingAssets/Table.png", 1, 1, 361, 101);
	rect = { 0,0, 361, 101};
	position = FG::Vector2D(0, 0);
}

UI::~UI()
{
}

void UI::Update(float deltaTime)
{
	rect = { (int)position.x, (int)position.y, 180, 50 };
}

void UI::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
}

void UI::UpdateScore(float deltatime)
{

}