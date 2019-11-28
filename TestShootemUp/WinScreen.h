#pragma once
#include "GameEntity.h"
#include "InputManager.h"
#include "Texture.h"


class WinScreen : public GameEntity //More or less same as death screen
{
private:

	InputManager* inputManager;
	GameEntity* topBar;
	Texture* winText;

	GameEntity* midBar;
	Texture* quitButton;
	Texture* cursor;

	Vector2 cursorStartPos;
	Vector2 cursorOffset;


public:

	WinScreen();
	~WinScreen();

	void Update();

	void Render();
};
