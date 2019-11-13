#pragma once
#include "GameEntity.h"
class Player : public GameEntity
{
public:
	void Update();
	void Render();

private:

	Vector2 position;
	Vector2 scale;

	float rotation;

	bool active;
	bool mouseMovement;

	void MovePlayer();
};

