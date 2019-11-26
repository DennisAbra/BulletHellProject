#pragma once
#include "StartScreen.h"

class SceneManager
{
private:


	static SceneManager* instance;

	InputManager* inputManager;

	StartScreen* startScreen;


public:

	static SceneManager* Instance();
	static void Release();

	void Update();
	void Render();

	enum SCENES { start, play };

	SCENES currentScene;
	

private:

	SceneManager();
	~SceneManager();

};
