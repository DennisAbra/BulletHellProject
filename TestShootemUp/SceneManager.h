#pragma once
#include "StartScreen.h"
#include "DeathScreen.h"
#include "WinScreen.h"

class SceneManager
{
private:


	static SceneManager* instance;

	WinScreen* winScreen;

	DeathScreen* deathScreen;

	InputManager* inputManager;

	StartScreen* startScreen;


public:

	bool quitGame = false;

	static SceneManager* Instance();
	static void Release();

	void Update();
	void Render();

	enum SCENES { start, play, death, win};

	SCENES currentScene;
	

private:

	SceneManager();
	~SceneManager();

};
