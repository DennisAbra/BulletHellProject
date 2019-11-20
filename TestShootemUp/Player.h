#pragma once
#include "GameEntity.h"
#include "InputManager.h"
#include "Texture.h"
#include "Timer.h"
#include "Bullet.h"
#include "Collision.h"
#include "Enemy.h"

class Bullet;

class Player : public GameEntity
{
public:

	Player(int posX, int posY, InputManager* input, const char* filePath);
	~Player();
	void Update();
	void Render();
	void OnCollision();
	void WasHit(); 
	void HandlePlayerDeath();

	void Invincible();

public:
	/* Player death, respawn and game over variables*/

	bool playerHit = false;
	bool playerInvincible = false;

	float maxInvincibilityFrameTimer = 1.0f;
	float invincibilityFrameTimer;

	float gameOverDelay;
	float gameOverTimer;
	bool gameOver;

	int playerMaxHealth = 5;
	int playerCurrentHealth;

	enum PlayerStates { alive, dead };

	static const int MAX_BULLETS = 10;

	Bullet* bullets[MAX_BULLETS];	  //Move to Bullet.h

	enum class  MovementStates { KEYBOARD = 0, MOUSE = 1 };
	Texture* texture;

private:

	void HandleFiring();
	void handlePlayerStates();

	void handleAliveState();
	void handleDeadState();


private:


	PlayerStates currentState;
	Bullet* bullet;
	InputManager* input;
	Enemy* enemy;

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

