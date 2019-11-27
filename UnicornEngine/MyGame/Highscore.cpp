#include "Highscore.h"
#include "Player.h"
#include "UI.h"

#include <EntityManager.h>


void Highscore::AddToFile(Player* player, std::string name)
{

	int newScore = player->GetScore();
	std::string newName = name;

	std::ifstream file("highscore.txt");
	std::ofstream output_file("tempfile.txt");

	std::cout << "New Highscore is: "; std::cout << newScore << std::endl;
	std::string newScoreString = std::to_string(newScore);


	if (file.is_open())
	{
		std::string line;
		std::string currentName = "";
		int currentLine = 1;
		bool moveUser = false;

		while (getline(file, line))
		{
			int scoreOnLine;

			if (currentLine % 2 != 0) //every odd line
			{
				scoreOnLine = std::stoi(line); //converts line to int for comparison
				if (newScore > scoreOnLine)
				{
					std::cout << newScore; std::cout << " is greater than "; std::cout << scoreOnLine; std::cout << ". Replacing number.." << std::endl;
					int oldScore = scoreOnLine; //saves old score
					std::string oldScoreString = std::to_string(oldScore); //converts it to string
					int spot = line.find(oldScoreString); //finds old score
					if (spot >= 0) //replaces existing content with the new score
					{
						std::string tempstring = line.substr(0, spot);
						tempstring += newScoreString;
						tempstring += line.substr(spot + oldScoreString.length(), line.length());
						line = tempstring;
					}
					newScore = oldScore; //then saves the old score to compare it to the next line, to shuffle scores down
					newScoreString = oldScoreString;
					moveUser = true;
				}
			}
			else
			{
				currentName = line;
				if (moveUser)
				{
					std::string oldName = currentName;
					int spot = line.find(currentName);
					if (spot >= 0) //Replaces the name in the same manner as above.
					{
						std::string tempstring = line.substr(0, spot);
						tempstring += newName;
						tempstring += line.substr(spot + currentName.length(), line.length());
						line = tempstring;
					}
					newName = oldName; //saves down the new name to replace.
					moveUser = false; //removes the check so the next cycle can begin.
				}
			}
			output_file << line << std::endl; //saves everything to temp file
			currentLine += 1; //time to check next line
		}
		file.close();
		output_file.close();
		remove("highscore.txt");
		int result = rename("tempfile.txt", "highscore.txt");
		remove("tempfile.txt");
	}
}
