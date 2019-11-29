#pragma once
#include <iostream> //TODO: Replace with actual GUI representation when a score screen is shown.
#include <fstream>
#include <string>
#include <map>
#include <Entity.h>

class Player;

class Highscore
{
public:
	void AddToFile(Player* player, std::string name);

	struct highscoreValue
	{
		std::string value;
	};

	struct arrayWrapper
	{
		highscoreValue list[20];
	};

	arrayWrapper DisplayScores(arrayWrapper wrapper);
private:
};