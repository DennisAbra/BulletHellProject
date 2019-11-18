#include "GameManager.h"

GameManager* GameManager::instance = NULL;

GameManager* GameManager::Instance()
{
	if (instance == NULL)
	{
		instance = new GameManager();
	}

	return instance;
}

void GameManager::Release()
{
	delete instance;
	instance = nullptr;
}

GameManager::GameManager() // Handle as Awake in Unity
{
	quit = false;

	graphics = Graphics::Instance();
	if (!Graphics::Initialized())
	{
		quit = true;
	}

	enemyPool = ObjectPooling::Instance();

	assetManager = AssetManager::Instance();

	inputManager = InputManager::Instance();

	audioManager = AudioManager::Instance();

	entityManager = EntityManager::Instance();

	timer = Timer::Instance();

	Enemy::CreatePaths();
	enemy = new Enemy(0);
	enemy2 = new Enemy(0, "SpriteSheet.png");

	player = new Player(400, 300, inputManager, "crawfish.png");
	entityManager->AddPlayer(player);

	entityManager->AddEnemies(enemy);
	entityManager->AddEnemies(enemy2);




}

GameManager::~GameManager()
{
	player = nullptr;

	entityManager->Instance()->Release();
	entityManager = nullptr;

	AudioManager::Release();
	audioManager = nullptr;

	AssetManager::Release();
	assetManager = nullptr;

	Graphics::Release();
	graphics = nullptr;

	InputManager::Release();
	inputManager = nullptr;

	Timer::Release();
	timer = nullptr;

}

void GameManager::EarlyUpdate()
{
	inputManager->Update();
}

void GameManager::Update() // Do Entity updates and input here
{
	entityManager->Update();
}

void GameManager::Render()
{
	graphics->ClearBackBuffer();
	//Do all draw calls here and before graphics->Render()

	entityManager->Render();

	graphics->Render();
}

void GameManager::LateUpdate() // Do collision or Physics checks here
{
	inputManager->UpdatePrevInput();
	timer->Reset();
}

void GameManager::Run()
{
	enemyPool->InitializeEnemyPool();

	for (int i = 0; i < enemyPool->POOL_SIZE; i++)
	{
		enemyPool->SetEnemyActive();

		if (enemyPool->enemies[i] != NULL) 
		{

			printf("Enemy spawing works!\n");
		}
	}

	while (!quit)
	{
		timer->Update();

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				enemyPool->CleanUpEnemies();
				quit = true;
			}
		}

		if (timer->DeltaTime() >= 1.0f / frameRate)
		{
			EarlyUpdate();
			Update();
			Render();
			LateUpdate();
		}
	}
}