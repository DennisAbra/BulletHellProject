#pragma once
#include "Enemy.h"
#include "Player.h"
#include "InputManager.h"


class BossArm : public Enemy
{
private:
	float rotation;

	
	InputManager* input;
	Player* player;
	SDL_Point point = {25, 30};

public:
	BossArm(int path, std::string textureName);
	BossArm(int path, std::string textureName, InputManager* input);
	
	~BossArm();
	Vector2 posOffset;

	void AimTowardsPlayer(Player* player);
	void MoveOffset();

	void Update() override;

};

