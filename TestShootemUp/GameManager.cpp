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

	assetManager = AssetManager::Instance();

	inputManager = InputManager::Instance();

	audioManager = AudioManager::Instance();

	timer = Timer::Instance();

	/*texture = new Texture("Hello World", "font.ttf", 72, {255, 0, 0});
	texture->Pos(Vector2(Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.4));
	texture2 = new Texture("Hello World", "font.ttf", 72, {255, 255, 0});
	texture2->Pos(Vector2(Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.7));*/

	//texture2->Parent(texture);
	Enemy::CreatePaths();
	enemy = new Enemy(0);




}

GameManager::~GameManager()
{
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

	if (texture)
	{
	delete texture;
	texture = nullptr;
	}
	if (texture2)
	{
	delete texture2;
	texture2 = nullptr;
	}

	delete enemy;
	enemy = nullptr;


}

void GameManager::EarlyUpdate()
{
	inputManager->Update();
}

void GameManager::Update() // Do Entity updates and input here
{
	enemy->Update();
}

void GameManager::Render()
{
	graphics->ClearBackBuffer();
	//Do all draw calls here and before graphics->Render()
	texture->Render();
	texture2->Render();
	enemy->Render();


	graphics->Render();
}

void GameManager::LateUpdate() // Do collision or Physics checks here
{
	inputManager->UpdatePrevInput();
	timer->Reset();
}


void GameManager::Run()
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