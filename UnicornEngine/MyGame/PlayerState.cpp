#include "PlayerState.h"
#include "Player.h"

class Player;

void PlayerState::Update(FG::Entity* entity, float deltaTime)
{
	static bool goingRight = true;

	FG::Vector2D position = FG::Vector2D(0, 0);
	if (entity->GetPosition().x < 280 && goingRight)
	{
		position.x += 1;
		if (entity->GetPosition().x + position.x >= 280)
		{
			goingRight = false;
		}
	}
	else
	{
		position.x += -1;

		if (entity->GetPosition().x - position.x <= 0)
		{
			goingRight = true;
		}
	}

	FG::Vector2D combinedPosition = entity->GetPosition() + position;

	entity->SetPosition(combinedPosition);
}