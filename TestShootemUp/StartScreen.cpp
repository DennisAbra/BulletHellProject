#include "StartScreen.h"

StartScreen::StartScreen()
{
	timer = Timer::Instance();
	input = InputManager::Instance();

	//Top Bar Entities
	topBar = new GameEntity(Graphics::Instance()->screenWidth * 0.5f, 80.0f);
	highScore = new Texture("HIGH-SCORE: ", "font.ttf", 32, { 200, 0, 0 });

	highScore->Parent(topBar);

	topBar->Parent(this);

	/* Play Mode Entities */
	playModes = new GameEntity(Graphics::Instance()->screenWidth * 0.5f, Graphics::Instance()->screenHeight * 0.55f);
	playButton = new Texture("PLAY", "font.ttf", 48, { 200, 0, 0 });
	quitButton = new Texture("QUIT", "font.ttf", 48, { 200, 0, 0 });
	cursor = new Texture("PlayerBullet.png");
	cursor->Scale(Vector2(0.1, 0.1));

	cursor->Parent(playModes);
	playButton->Parent(playModes);
	quitButton->Parent(playModes);

	cursor->Pos(Vector2(-75.0f, 35.0f));
	playButton->Pos(Vector2(0.0f, 35.0f));
	quitButton->Pos(Vector2(0.0f, 85.0f));
	highScore->Pos(Vector2(-30.0f, 0.0f));

	playModes->Parent(this);

	cursorStartPos = cursor->Pos(local);
	cursorOffSet = Vector2(0.0f, 50.0f);
	selectedMode = 0;

	//Logo
	logo = new Texture("Logo.png", 0, 0, 2480, 1963);
	logo->Scale(Vector2(0.15, 0.15));
	logo->Pos(Vector2(Graphics::Instance()->screenWidth * 0.5f, Graphics::Instance()->screenHeight * 0.4f));
	logo->Parent(this);

	//Screen animation Variables

	ResetAnimation();
}

StartScreen::~StartScreen()
{
	delete playModes;
	playModes = nullptr;

	delete topBar;
	topBar = nullptr;

	delete playButton;
	playButton = nullptr;

	delete highScore;
	highScore = nullptr;

	delete quitButton;
	quitButton = nullptr;

	delete logo;
	logo = nullptr;

	delete cursor;
	cursor = nullptr;
}

void StartScreen::ResetAnimation()
{
	animationStartPos = Vector2(Graphics::Instance()->screenWidth * 1.0f, Graphics::Instance()->screenHeight);
	animationEndPos = Vec2_Zero;
	animationTotalTime = 10.0f;
	animationTimer = 0.0f;
	animationDone = false;

	Pos(animationStartPos);
}

int StartScreen::SelectedMode()
{
	return selectedMode;
}

void StartScreen::ChangeSelectedMode(int change)
{
	selectedMode += change;

	if (selectedMode < 0)
	{
		selectedMode = 1;
	}
	else if (selectedMode > 1)
	{
		selectedMode = 0;
	}

	cursor->Pos(cursorStartPos + cursorOffSet * selectedMode);
}

void StartScreen::Update()
{
	if (!animationDone)
	{
		animationTimer += timer->DeltaTime();
		Pos(Lerp(animationStartPos, animationEndPos, animationTimer / animationTotalTime));

		if (animationTimer >= animationTotalTime)
		{
			animationDone = true;
		}
	}

	if (input->KeyPressed(SDL_SCANCODE_DOWN))
	{
		ChangeSelectedMode(1);
		if (selectedMode == 0 && input->KeyPressed(SDL_SCANCODE_RETURN))
		{

		}
	}
	else if (input->KeyPressed(SDL_SCANCODE_UP))
	{
		ChangeSelectedMode(-1);
	}
}

void StartScreen::Render()
{
	playButton->Render();
	highScore->Render();
	quitButton->Render();
	logo->Render();
	cursor->Render();

}