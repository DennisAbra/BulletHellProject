#include "SceneManager.h"

SceneManager* SceneManager::instance = NULL;

SceneManager* SceneManager::Instance()
{
	if (instance == NULL)
	{
		instance = new SceneManager();
	}

	return instance;
}

void SceneManager::Release()
{
	delete instance;
	instance = NULL;
}

SceneManager::SceneManager()
{
	inputManager = InputManager::Instance();
	startScreen = new StartScreen();

	currentScene = SceneManager::start;
}

SceneManager::~SceneManager()
{
	inputManager = NULL; //Released in game manager

	delete startScreen;
	startScreen = NULL;
}


void SceneManager::Update()
{
	switch (currentScene)
	{
	case start:

		startScreen->Update();

		if (inputManager->KeyPressed(SDL_SCANCODE_RETURN) && startScreen->selectedMode == 0)
		{
			currentScene = play;
			startScreen->ResetAnimation();
		}
		else if (inputManager->KeyPressed(SDL_SCANCODE_RETURN) && startScreen->selectedMode == 1)
		{
			//quit
		}

		break;
	}
}

void SceneManager::Render()
{
	switch (currentScene)
	{
	case start:
		
		startScreen->Render();
		break;

	case play:
		break;
	}
}