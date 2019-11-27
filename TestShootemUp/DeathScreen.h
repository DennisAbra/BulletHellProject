#pragma once
#include "GameEntity.h"
#include "InputManager.h"
#include "Texture.h"

class DeathScreen : public GameEntity
{
private:
	InputManager* inputManager;
	/* TOP BAR ENTITIES */
	GameEntity* topBar;
	Texture* deathText;
	/* BUTTONS */

	GameEntity* midButtons;
	Texture* quitButton;
	Texture* cursor;

	Vector2 cursorStartPos;
	Vector2 cursorOffset;

	/* Logo */
	Texture* Logo;

public:

	int currentScore;


	DeathScreen();
	~DeathScreen();

	void Update();

	void Render();

};