#pragma once
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "EntityManager.h"
#include "ObjectPooling.h"
#include "PhysManager.h"
#include "SceneManager.h"

class GameManager
{
private:

	static GameManager* instance;
	bool play;

	ObjectPooling* enemyPool;
	Graphics* graphics;
	AssetManager* assetManager;
	InputManager* inputManager;
	AudioManager* audioManager;
	EntityManager* entityManager;
	PhysManager* physManager;

	const int frameRate = 60;
	Timer* timer;

	SDL_Event event;

	SceneManager* sceneManager;

	Enemy* enemy;
	Enemy* enemy2;

	Player* player;
	Boss* boss;
	BossArm* bossArm;
	Texture* texture;

	GameManager();
	~GameManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Render();

public:
	bool quit;

	//bool inMenu = true;

	static GameManager* Instance();
	static void Release();

	void Run();
};
