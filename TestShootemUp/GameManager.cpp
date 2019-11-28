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

	sceneManager = SceneManager::Instance();

	enemyPool = ObjectPooling::Instance();

	assetManager = AssetManager::Instance();

	inputManager = InputManager::Instance();

	audioManager = AudioManager::Instance();

	entityManager = EntityManager::Instance();

	physManager = PhysManager::Instance();
	physManager->SetLayerCollisionMask(PhysManager::CollisionLayers::Friendly, PhysManager::CollisionFlags::Hostile | PhysManager::CollisionFlags::HostileProjectile);

	physManager->SetLayerCollisionMask(PhysManager::CollisionLayers::FriendlyProjectile, PhysManager::CollisionFlags::Hostile);

	physManager->SetLayerCollisionMask(PhysManager::CollisionLayers::Hostile, PhysManager::CollisionFlags::Friendly | PhysManager::CollisionFlags::FriendlyProjectiles);

	physManager->SetLayerCollisionMask(PhysManager::CollisionLayers::HostileProjectile, PhysManager::CollisionFlags::Friendly);

	timer = Timer::Instance();

	Enemy::CreatePaths();

	sceneManager = SceneManager::Instance();
	
	player = new Player(Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.5f, inputManager, "PartyKrister.png");

	entityManager->AddPlayer(player);

	enemyPool->InitializeEnemyPool();
	for (int i = 0; i < enemyPool->POOL_SIZE; i++)
	{
		enemyPool->SetEnemyActive();
		entityManager->AddEnemies(enemyPool->enemies[i]);

		enemyPool->enemies[i]->Pos(Vector2(enemyPool->enemies[i]->Pos().x, -60.0f * (i + 1)));
		enemyPool->enemies[i]->startPos = Vector2(enemyPool->enemies[i]->Pos().x, -60.0f * (i + 1));
	}
}

GameManager::~GameManager()
{
	SceneManager::Release();
	sceneManager = nullptr;

	PhysManager::Release();
	physManager = nullptr;

	enemyPool->Release();
	enemyPool = nullptr;

	player = nullptr;

	entityManager->Instance()->Release();
	entityManager = nullptr;

	AssetManager::Release();
	assetManager = nullptr;

	AudioManager::Release();
	audioManager = nullptr;




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
	static bool bossAlive = false;
	static bool isPlayingMusic = false;

	switch (sceneManager->currentScene)
	{
	case SceneManager::play:
		entityManager->Update();

		if (!isPlayingMusic)
		{
			
			//audioManager->PlayMusic("music.mp3");
			isPlayingMusic = true;
		}

		if (Enemy::deadEnemyCounter == 15 && !bossAlive)
		{
			boss = new Boss(3, "PepsiBoss.png", player);
			boss->texture->Scale(Vector2(0.5f, 0.5f));
			entityManager->AddBoss(boss);

			bossArm = new BossArm(3, "BossArm.png", inputManager, player);
			bossArm->texture->Scale(Vector2(0.5f, 0.5f));
			bossArm->Parent(boss);
			bossArm->Pos(Vec2_Zero + bossArm->posOffset);

			entityManager->AddBossArm(bossArm);
			bossArm->AimTowardsPlayer(player);
			bossAlive = true;
			Enemy::bossSpawned = true;
		}
		break;

	case SceneManager::start:
		sceneManager->Update();
		break;
	}

	switch (sceneManager->currentScene) //For input
	{
	case SceneManager::play:

		if (bossAlive == false)
		{
			audioManager->PlayMusic("WinSound.mp3", 1);
		}

		if (inputManager->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			sceneManager->currentScene = SceneManager::start;
			audioManager->PlayMusic("Vroom.mp3", 1);

		}

		else if (player->playerCurrentHealth <= 0)
		{
			sceneManager->currentScene = SceneManager::death;
			if (sceneManager->quitGame == true)
			{
				quit = true;
			}
		}
		break;

	case SceneManager::death:

		if (inputManager->KeyPressed(SDL_SCANCODE_RETURN))
		{
			quit = true;
		}

		break;
	}
}

void GameManager::Render()
{
	graphics->ClearBackBuffer();

	switch (sceneManager->currentScene)
	{
	case SceneManager::play:

		entityManager->Render();

		break;

	case SceneManager::start:
		sceneManager->Render();
		break;

	case SceneManager::death:
		sceneManager->Render();
		break;
	}
	//Do all draw calls here and before graphics->Render()
	graphics->Render();
}

void GameManager::LateUpdate() // Do collision or Physics checks here
{
	physManager->Update();
	inputManager->UpdatePrevInput();
	timer->Reset();
}

void GameManager::Run() // Don't test stuff here. Use the Update functions
{
	while (!quit)
	{
		timer->Update();

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		if (sceneManager->quitGame == true)
		{
			quit = true;
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