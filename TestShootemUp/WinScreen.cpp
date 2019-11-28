#include "WinScreen.h"
WinScreen::WinScreen()
{
	inputManager = InputManager::Instance();

	/* TOP BAR ENITITES */

	topBar = new GameEntity(Graphics::Instance()->screenWidth * 0.5f, 80.0f);
	winText = new Texture("You Win!", "font.ttf", 48, { 0, 255, 0 });

	/* MID BAR ENTITIES */

	midBar = new GameEntity(Graphics::Instance()->screenWidth * 0.5f, Graphics::Instance()->screenHeight * 0.5f);
	quitButton = new Texture("QUIT", "font.ttf", 48, { 200, 0, 0 });

	cursor = new Texture("PlayerBullet.png");
	cursor->Scale(Vector2(0.1, 0.1));

	cursor->Parent(midBar);
	quitButton->Parent(midBar);

	cursor->Pos(Vector2(-75.0f, 35.0f));
	quitButton->Pos(Vector2(0.0f, 35.0f));
	winText->Pos(Vector2(Graphics::Instance()->screenWidth * 0.5f, Graphics::Instance()->screenHeight * 0.3f));

	midBar->Parent(this);

	cursorStartPos = cursor->Pos(local);
	cursorOffset = Vector2(0.0f, 50.0f);
}

WinScreen::~WinScreen()
{
	delete topBar;
	topBar = nullptr;

	delete midBar;
	midBar = nullptr;

	delete quitButton;
	quitButton = nullptr;

	delete cursor;
	cursor = nullptr;

	delete winText;
	winText = nullptr;
}

void WinScreen::Update()
{

}

void WinScreen::Render()
{
	quitButton->Render();
	cursor->Render();
	winText->Render();
}
