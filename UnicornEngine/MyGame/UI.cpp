#include "UI.h"

#include <SpriteManager.h>
#include <EntityManager.h>
#include "Player.h";

UI::UI(const char* element, FG::SpriteManager* spriteManager) : spriteManager(spriteManager)
{
	Active = true;
	sprite = spriteManager->CreateSprite("../TestingAssets/Table.png", 1, 1, 361, 101);
	pilotPortrait = spriteManager->CreateSprite("../TestingAssets/UniPilot.png", 1, 1, 38, 40);
	heart = spriteManager->CreateSprite("../TestingAssets/Heart.png", 1, 1, 32, 32);
	rect = { 0,0, 361, 101};
	position = FG::Vector2D(0, 0);

	pilotPortraitRect = { 0, 800, 76, 80 };
	heartRect = { 70, 800, 32, 32 };
}

UI::~UI()
{
}

void UI::Update(float deltaTime)
{
	rect = { (int)position.x, 800, 76, 80 };
}

void UI::Render(FG::Camera* const camera)
{
	spriteManager->Draw(pilotPortrait, pilotPortraitRect);
	DrawHearts();
}

void UI::UpdateScore(float deltatime)
{

}

void UI::DrawHearts()
{
	Player* player = dynamic_cast<Player*>(FG::EntityManager::Instance()->GetPlayer());

	for (int i = 0; i < player->LifesLeft(); i++)
	{
		spriteManager->Draw(heart, { heartRect.x + (i * 35), heartRect.y, heartRect.w, heartRect.h });
	}
}