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

	texture = new Texture("Hello World", "font.ttf", 72, {255, 0, 0});
	texture->Pos(Vector2(Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.4));
	texture2 = new Texture("Hello World", "font.ttf", 72, {0, 0, 0});
	texture2->Pos(Vector2(Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.7));

	texture2->Parent(texture);


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

	delete texture;
	texture = nullptr;

	delete texture2;
	texture2 = nullptr;
}

void GameManager::EarlyUpdate()
{
	inputManager->Update();
}

void GameManager::Update() // Do Entity updates and input here
{
	if (inputManager->KeyPressed(SDL_SCANCODE_W))
	{
		texture2->Parent(texture);
	}

	if (inputManager->MouseButtonPressed(InputManager::middle))
	{
		texture2->Parent(nullptr);
	}


	texture->Rotate(10 * timer->DeltaTime());
}

void GameManager::Render()
{
	graphics->ClearBackBuffer();
	//Do all draw calls here and before graphics->Render()
	texture->Render();
	texture2->Render();


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