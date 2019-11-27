#pragma once
#include "GameEntity.h"
#include "InputManager.h"
#include "AnimatedTexture.h"
#include "Timer.h"
#include "Bullet.h"
#include "Collision.h"

class Bullet;

class Player : public PhysEntity
{
public:

	Player(int posX, int posY, InputManager* input, const char* filePath);
	~Player();
	void Update();
	void Render();

	bool WasHit(); 
	void Hit(PhysEntity* other) override;
	void HandlePlayerDeath();

	void Invincible();

public:
	/* Player death, respawn and game over variables*/

	Player* me;

	bool playerHit = false;
	bool playerInvincible = false;
	bool wasHit;

	float maxInvincibilityFrameTimer = 1.0f;
	float invincibilityFrameTimer;

	float gameOverDelay;
	float gameOverTimer;
	bool gameOver;

	int playerMaxHealth = 3;
	int playerCurrentHealth;

	Vector2 emptyGlassStartPos = { 75, Graphics::screenHeight - 100 };
	Vector2 glassBottomPos = { 75, Graphics::screenHeight - 50 };
	Vector2 glassMiddlePos = { 75, Graphics::screenHeight - 105 };
	Vector2 glassTopPos = { 75, Graphics::screenHeight - 160 };

	enum PlayerStates { alive, dead };

	static const int MAX_BULLETS = 10;

	Bullet* bullets[MAX_BULLETS];

	enum class  MovementStates { KEYBOARD = 0, MOUSE = 1 };
	Texture* texture;
	Texture* emptyGlass;
	Texture* glassBottom;
	Texture* glassMiddle;
	Texture* glassTop;

private:

	void HandleFiring();
	void handlePlayerStates();

	bool IgnoreCollisions() override;
	void handleAliveState();
	void handleDeadState();

private:

	PlayerStates currentState;
	//Bullet* bullet;
	InputManager* input;
	//Enemy* enemy;

	Vector2 position;
	Vector2 scale;
	Vector2 firePoint;

	Timer* timer;

	AnimatedTexture* animatedTexture;

	float rotation;
	float speed = 50.f;
	bool active;
	bool mouseMovement;
	bool ShouldNormalizeVector();

	MovementStates movementState;
	bool CheckMouseScreenBounds();
	void MovePlayer();
	void SwitchMovement();
};

