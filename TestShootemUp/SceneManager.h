#pragma once
#include "StartScreen.h"
#include "DeathScreen.h"

class SceneManager
{
private:


	static SceneManager* instance;

	DeathScreen* deathScreen;

	InputManager* inputManager;

	StartScreen* startScreen;


public:

	bool quitGame = false;

	static SceneManager* Instance();
	static void Release();

	void Update();
	void Render();

	enum SCENES { start, play, death};

	SCENES currentScene;
	

private:

	SceneManager();
	~SceneManager();

};
