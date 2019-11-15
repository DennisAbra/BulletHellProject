#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "EntityManager.h"


class GameManager
{
private:

	static GameManager* instance;
	bool quit;

	Graphics* graphics;
	AssetManager* assetManager;
	InputManager* inputManager;
	AudioManager* audioManager;
	EntityManager* entityManager;
	

	const int frameRate = 60;
	Timer* timer;

	SDL_Event event;

	Enemy* enemy;
	Enemy* enemy2;

	Player* player;

	GameManager();
	~GameManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Render();

public:

	static GameManager* Instance();
	static void Release();

	void Run();
};