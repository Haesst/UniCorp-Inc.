#pragma once

#include <string>
#include <Entity.h>
#include <Vector2D.h>

namespace FG //i have identified that these two classes exist in FG/engine.
{
	class SpriteManager;
	class Camera;
}

class Enemy : public FG::Entity
{
public:
	Enemy(int param[4], const char* filename, FG::SpriteManager* spriteManagerRef);
	~Enemy();

	virtual void Update(float deltaTime) override; //*?
	virtual void Render(FG::Camera* const camera) override;

	//FG::Vector2D position;

private:
	Enemy();
	void MoveEnemy(float deltaTime);
	//FG::Vector2D position;
	FG::SpriteManager* spriteManager;

	// Inherited via Entity
	virtual void onCollision(Tag tagau) override;

};