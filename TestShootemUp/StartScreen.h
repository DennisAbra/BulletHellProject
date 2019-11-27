#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Timer.h"
#include "AudioManager.h"

class StartScreen : public GameEntity
{
private:

	AudioManager* audioManager;
	Timer* timer;
	InputManager* input;

	//Top bar Entities
	GameEntity* topBar;
	GameEntity* playModes;

	//Play entities
	Texture* playButton;
	Texture* quitButton;
	Texture* cursor;

	Vector2 cursorStartPos;
	Vector2 cursorOffSet;

	//logo
	Texture* logo;

	//Screen Animation Variables
	Vector2 animationStartPos;
	Vector2 animationEndPos;
	float animationTotalTime;
	float animationTimer;
	bool animationDone;

public:
	int selectedMode;

	//Vector2 topBarPos = { Graphics::Instance()->screenWidth * 0.5f, 80.0f };

	StartScreen();
	~StartScreen();

	void ResetAnimation();

	void ChangeSelectedMode(int change);

	int SelectedMode(); //Return selected mode

	void Update();

	void Render();

};


