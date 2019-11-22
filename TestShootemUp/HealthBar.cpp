#include "HealthBar.h"

HealthBar::HealthBar()
{
	//healthBar = new AnimatedTexture("HealthBar", 10, 10, 5, 5, 5, 1.0f, 1);
}

HealthBar::~HealthBar()
{
	delete healthBar;
	healthBar = nullptr;
}

void HealthBar::SetMaxHealthBar()
{
	frameCount = player->playerMaxHealth;
}

void HealthBar::reduceHealth()
{
	//currentFrame++;
	//Called from player class probably
	//if(frameCount == 0) //Player is dead, launch game over screen.
}
