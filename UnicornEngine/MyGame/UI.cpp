#include "UI.h"

#include <SpriteManager.h>
#include <EntityManager.h>
#include <Camera.h>
#include <Sprite.h>
#include "Player.h";

#include <string>
#include <iostream>

UI::UI()
{
}

UI::~UI()
{
	TTF_Quit();
}

void UI::Update(float deltaTime)
{
}

void UI::Render(FG::Camera* const camera)
{
	DrawPortrait();
	DrawHearts();
	DrawScore();
}

UI* UI::Instance()
{
	static UI* ui = new UI();
	return ui;
}

void UI::Initialize(FG::SpriteManager* spriteManager, SDL_Renderer* renderer, SDL_Window* window)
{
	TTF_Init();

	this->spriteManager = spriteManager;

	player = dynamic_cast<Player*>(FG::EntityManager::Instance()->GetPlayer());

	//sprite = spriteManager->CreateSprite("../TestingAssets/Table.png", 1, 1, 361, 101);
	pilotPortraitStage1 = spriteManager->CreateSprite("../TestingAssets/UniPilot.png", 1, 1, 38, 40);
	pilotPortraitStage2 = spriteManager->CreateSprite("../TestingAssets/UniPilot_Stage2.png", 1, 1, 38, 40);
	pilotPortraitStage3 = spriteManager->CreateSprite("../TestingAssets/UniPilot_Stage3.png", 1, 1, 38, 40);
	heart = spriteManager->CreateSprite("../TestingAssets/Heart.png", 1, 1, 32, 32);

	pilotPortraitRect = { 0, 800, 76, 80 };
	heartRect = { 70, 800, 32, 32 };
	playerScoreRect = { 400, 800, 200, 20 };

	scoreFont = TTF_OpenFont("../TestingAssets/MinecraftCHMC.ttf", 28);
	this->renderer = renderer;
	this->window = window;

	UpdateScore();
}

void UI::UpdateScore()
{
	SDL_FreeSurface(playerScoreSurface);
	SDL_DestroyTexture(scoreTexture);

	std::string scoreText = "Score: " + std::to_string(player->GetScore());
	playerScoreSurface = TTF_RenderText_Solid(scoreFont, scoreText.c_str() , { 255,255,255,255 });
	scoreTexture = SDL_CreateTextureFromSurface(renderer, playerScoreSurface);

	int width = playerScoreSurface->w;
	int height = playerScoreSurface->h;
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	playerScoreRect = { windowWidth - 50 - width, windowHeight - 50, width, height };
	playerScoreSprite = new FG::Sprite(scoreTexture, 1, 1, width, height);
}

void UI::DrawHearts()
{

	for (int i = 0; i < player->LifesLeft(); i++)
	{
		spriteManager->Draw(heart, { heartRect.x + (i * 35), heartRect.y, heartRect.w, heartRect.h });
	}
}

void UI::DrawPortrait()
{

	switch (player->LifesLeft())
	{
	case 3:
		spriteManager->Draw(pilotPortraitStage1, pilotPortraitRect);
		break;
	case 2:
		spriteManager->Draw(pilotPortraitStage2, pilotPortraitRect);
		break;
	case 1:
		spriteManager->Draw(pilotPortraitStage3, pilotPortraitRect);
		break;
	}
}

void UI::DrawScore()
{
	if (scoreTexture == NULL)
	{
		std::cout << "Score texture = nullptr" << std::endl;
	}

	if (playerScoreSurface == NULL)
	{
		std::cout << "Score surface = nullptr" << std::endl;
	}

	//SDL_FreeSurface(playerScoreSurface);
	spriteManager->Draw(playerScoreSprite, playerScoreRect);
	//delete playerScoreSprite;
}