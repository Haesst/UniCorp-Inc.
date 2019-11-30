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
	currentPowerUp = player->GetCurrentPowerup();

	if (currentPowerUp != "")
	{
		powerUpTimeLeft = player->GetPowerupDuration();
		if (powerUpTimeLeft <= 1.0f)
		{
			flashCounter += deltaTime;
			if (flashCounter >= timeBetweenFlash)
			{
				flashAlpha = !flashAlpha;
				flashCounter = 0;
			}
		}
	}
}

void UI::Render(FG::Camera* const camera)
{
	DrawPortrait();
	DrawHearts();
	DrawScore();
	DrawPowerup();
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

	int windowWidth = 0;
	int windowHeight = 0;

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	//sprite = spriteManager->CreateSprite("../TestingAssets/Table.png", 1, 1, 361, 101);
	pilotPortraitStage1 = spriteManager->CreateSprite("../TestingAssets/UniPilot.png", 1, 1, 38, 40);
	pilotPortraitStage2 = spriteManager->CreateSprite("../TestingAssets/UniPilot_Stage2.png", 1, 1, 38, 40);
	pilotPortraitStage3 = spriteManager->CreateSprite("../TestingAssets/UniPilot_Stage3.png", 1, 1, 38, 40);
	heart = spriteManager->CreateSprite("../TestingAssets/Heart.png", 1, 1, 32, 32);
	highscoreWindow = spriteManager->CreateSprite("../TestingAssets/Window.png", 1, 1, 940, 1400);

	tripleShotSprite = spriteManager->CreateSprite("../TestingAssets/PowerUpSpread.png", 1,1,32,32);
	spreadShotSprite = spriteManager->CreateSprite("../TestingAssets/PowerUpMultiSpread.png", 1, 1, 32, 32);
	ringShotSprite = spriteManager->CreateSprite("../TestingAssets/PowerUpRingshot.png", 1, 1, 32, 32);
	playerSpeedSprite = spriteManager->CreateSprite("../TestingAssets/PowerUpPlayerSpeed.png", 1,1,32,32);
	fireSpeedSprite = spriteManager->CreateSprite("../TestingAssets/PowerUpFireSpeed.png", 1,1,32,32);

	pilotPortraitRect = { 0, windowHeight - 100, 76, 80 };
	heartRect = { 70, windowHeight - 100, 32, 32 };
	powerupRect = { 80, windowHeight - 60, 32, 32 };

	playerScoreRect = { windowWidth - 100, windowHeight - 100, 200, 20 };
	highscoreRect = { 0, -900, 640, 900};

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

void UI::ResetUI()
{
	player = dynamic_cast<Player*>(FG::EntityManager::Instance()->GetPlayer());
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
	if (player->LifesLeft() == 1)
	{
		spriteManager->Draw(pilotPortraitStage3, pilotPortraitRect);
	}
	else if (player->LifesLeft() == 2)
	{
		spriteManager->Draw(pilotPortraitStage2, pilotPortraitRect);
	}
	else
	{
		spriteManager->Draw(pilotPortraitStage1, pilotPortraitRect);
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

void UI::DrawPowerup()
{
	if (currentPowerUp != "")
	{
		FG::Sprite* spriteToDraw = GetPowerupSprite();
		if (spriteToDraw != nullptr)
		{
			if (powerUpTimeLeft < 1.0f)
			{
				if (flashAlpha)
				{
					spriteManager->Draw(spriteToDraw, powerupRect, 0.0f);
				}
				else
				{
					spriteManager->Draw(spriteToDraw, powerupRect, 255.0f);
				}
			}
			else
			{
				spriteManager->Draw(spriteToDraw, powerupRect, 255.0f);
			}
		}
	}
}

FG::Sprite* UI::GetPowerupSprite()
{
	if (currentPowerUp == "Multispread")
	{
		return spreadShotSprite;
	}
	else if (currentPowerUp == "Ringshot")
	{
		return ringShotSprite;
	}
	else if (currentPowerUp == "Spread")
	{
		return tripleShotSprite;
	}
	else if (currentPowerUp == "playerSpeed")
	{
		return playerSpeedSprite;
	}
	else if (currentPowerUp == "firespeed")
	{
		return fireSpeedSprite;
	}

	return nullptr;
}

SDL_Rect UI::DrawHighscoreWindow()
{
	spriteManager->Draw(highscoreWindow, highscoreRect);
	return highscoreRect;
}

void UI::LowerHighscoreWindow(SDL_Rect highscoreRect)
{
	spriteManager->Draw(highscoreWindow, highscoreRect);
}

void UI::DrawHighscores(std::string line, int w, int h)
{
	SDL_FreeSurface(highscoreSurface);
	SDL_DestroyTexture(highscoreTexture);

	std::string text = line;
	highscoreSurface = TTF_RenderText_Solid(scoreFont, text.c_str(), { 255,255,255,255 });
	highscoreTexture = SDL_CreateTextureFromSurface(renderer, highscoreSurface);

	int width = 50;
	int height = 50;
	highscoreTextRect = { w, h, 200, 50};

	highscoreSprite = new FG::Sprite(highscoreTexture, 1, 1, 100, 50);
	spriteManager->Draw(highscoreSprite, highscoreTextRect);
}
