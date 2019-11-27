#include "DeathScreen.h"

DeathScreen::DeathScreen()
{
	inputManager = InputManager::Instance();
	/* TOP BAR ENTITIES */
	topBar = new GameEntity(Graphics::Instance()->screenWidth * 0.5f, 80.0f);
	deathText = new Texture("YOU DIED!", "font.ttf", 48, { 200, 0, 0 });

	topBar->Parent(this);

	/* Buttons */ //May add view High Score
	midButtons = new GameEntity(Graphics::Instance()->screenWidth * 0.5f, Graphics::Instance()->screenHeight * 0.55f);
	quitButton = new Texture("QUIT", "font.ttf", 48, { 200, 0, 0 });

	cursor = new Texture("PlayerBullet.png");
	cursor->Scale(Vector2(0.1, 0.1));


	cursor->Parent(midButtons);
	quitButton->Parent(midButtons);

	cursor->Pos(Vector2(-75.0f, 35.0f));
	quitButton->Pos(Vector2(0.0f, 35.0f));
	deathText->Pos(Vector2(Graphics::Instance()->screenWidth * 0.5f, Graphics::Instance()->screenHeight * 0.3f));

	midButtons->Parent(this);

	cursorStartPos = cursor->Pos(local);
	cursorOffset = Vector2(0.0f, 50.0f);
}

DeathScreen::~DeathScreen()
{
	delete topBar;
	topBar = nullptr;

	delete midButtons;
	midButtons = nullptr;

	delete quitButton;
	quitButton = nullptr;

	delete cursor;
	cursor = nullptr;

	delete deathText;
	deathText = nullptr;
}

void DeathScreen::Update()
{

}

void DeathScreen::Render()
{
	quitButton->Render();
	cursor->Render();
	deathText->Render();
}