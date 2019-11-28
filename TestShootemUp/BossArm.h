#pragma once
#include "Enemy.h"
#include "Player.h"
#include "InputManager.h"

class BossArm : public Enemy
{
private:
	float rotation;
	Vector2 distanceToPlayer;
	
	InputManager* input;
	Player* player;
	SDL_Point point = {25, 30}; // this + rotation + offset


public:
	BossArm(int path, std::string textureName, Player* player);
	BossArm(int path, std::string textureName, InputManager* input, Player* player);
	GameEntity* firePointEntity;
	~BossArm();
	Vector2 posOffset;

	static bool armIsAlive;

	void AimTowardsPlayer(Player* player);

	void Update() override;

};

