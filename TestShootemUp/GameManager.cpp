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

	physManager = PhysManager::Instance();
	physManager->SetLayerCollisionMask(PhysManager::CollisionLayers::Friendly, PhysManager::CollisionFlags::Hostile | PhysManager::CollisionFlags::HostileProjectile);

	physManager->SetLayerCollisionMask(PhysManager::CollisionLayers::FriendlyProjectile, PhysManager::CollisionFlags::Hostile);

	physManager->SetLayerCollisionMask(PhysManager::CollisionLayers::Hostile, PhysManager::CollisionFlags::Friendly | PhysManager::CollisionFlags::FriendlyProjectiles);

	physManager->SetLayerCollisionMask(PhysManager::CollisionLayers::HostileProjectile, PhysManager::CollisionFlags::Friendly);

	timer = Timer::Instance();

	Enemy::CreatePaths();


	
	player = new Player(Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.5f, inputManager, "PartyKrister.png");
	entityManager->AddPlayer(player);

	boss = new Boss(3, "PepsiBoss.png");
	boss->texture->Scale(Vector2(0.5f, 0.5f));
	entityManager->AddBoss(boss);

	bossArm = new BossArm(3,"BossArm.png", inputManager);
	bossArm->texture->Scale(Vector2(0.5f, 0.5f));
	bossArm->Parent(boss);
	bossArm->Pos(bossArm->Parent()->Pos() + bossArm->posOffset);
	
	
	entityManager->AddBossArm(bossArm);
	bossArm->AimTowardsPlayer(player);


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

	PhysManager::Release();
	physManager = nullptr;

	enemyPool->Release();
	enemyPool = nullptr;

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

		if (timer->DeltaTime() >= 1.0f / frameRate)
		{
			EarlyUpdate();
			Update();
			Render();
			LateUpdate();
		}
	}
}