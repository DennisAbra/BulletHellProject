#include "HealthBar.h"

HealthBar* HealthBar::instance = NULL;

HealthBar* HealthBar::Instance()
{
	if (instance == NULL)
	{
		instance = new HealthBar();
	}

	return instance();
}


HealthBar::HealthBar()
{
	
}

HealthBar::~HealthBar()
{

}

void HealthBar::SetMaxHealthBar()
{
	EmptyGlass->Pos(Vector2{50, 50});
}

void HealthBar::reduceHealth()
{
	if (glassCounter == 3) //Glass is full
	{
		glassCounter--;
		TopDrink->Active(false);
		return;
	}

	if (glassCounter == 2)
	{
		glassCounter--;
		MiddleDrink->Active(false);
		return;
	}

	if (glassCounter == 1)
	{
		glassCounter--;
		BottomDrink->Active(false);
		return;
	}

	//If player takes damage, set part of glass inactive.
}

