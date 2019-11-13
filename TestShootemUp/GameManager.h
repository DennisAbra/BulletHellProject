#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Enemy.h"


class GameManager
{
private:

	static GameManager* instance;
	bool quit;

	Graphics* graphics;
	AssetManager* assetManager;
	InputManager* inputManager;
	AudioManager* audioManager;

	const int frameRate = 60;
	Timer* timer;

	SDL_Event event;
	Texture* texture;
	Texture* texture2;
	Enemy* enemy;

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
