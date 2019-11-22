#pragma once
#include "AnimatedTexture.h"
#include "Player.h"
class HealthBar : public GameEntity
{
private:
	static HealthBar* instance;

public: //Methods
	static HealthBar* Instance();

	 HealthBar();
	 ~HealthBar();

	 void SetMaxHealthBar(); //To be called in cTor

	 void reduceHealth();

public: //Variables



};
