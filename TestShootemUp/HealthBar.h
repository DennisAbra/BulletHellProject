#pragma once
#include "AnimatedTexture.h"
#include "Player.h"
class HealthBar
{
public: //Methods
	 HealthBar();
	 ~HealthBar();

	 AnimatedTexture* healthBar;

	 void SetMaxHealthBar(); //To be called in cTor

	 void reduceHealth();

public: //Variables

	Player* player;
	int frameCount;
};
