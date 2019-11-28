#pragma once
#include "Enemy.h"
#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "ObjectPooling.h"
#include "BossArm.h"

class Boss : public Enemy
{
private:	

	void Hit(PhysEntity* other) override;

public:
	bool killBoss = false;
	Boss(int path);
	Boss(int path, std::string textureName, Player* player);
	virtual ~Boss();

	void HandleFlyInState() override;
	


	


};

