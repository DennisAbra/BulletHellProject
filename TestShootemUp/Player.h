#pragma once
#include "GameEntity.h"
#include "InputManager.h"
#include "Texture.h"
#include "Timer.h"
#include "Bullet.h"
#include "Collision.h"

class Bullet;

class Player : public GameEntity
{
public:

	Player(int posX, int posY, InputManager* input, const char* filePath);
	~Player();
	void Update();
	void Render();

	enum class  MovementStates { KEYBOARD = 0, MOUSE = 1 };
	Texture* texture;


private:

	void HandleFiring();
	void handlePlayerStates();

	void handleAliveState();
	void handleDeadState();


private:

	enum PlayerStates { alive, dead };
	PlayerStates currentState;
	Bullet* bullet;
	InputManager* input;


	Vector2 position;
	Vector2 scale;
	Vector2 firePoint;

	Timer* timer;

	float rotation;
	float speed = 50.f;
	bool active;
	bool mouseMovement;
	bool ShouldNormalizeVector();

	MovementStates movementState;
	bool CheckMouseScreenBounds();
	void MovePlayer();
	void SwitchMovement();

	
public:
	int playerMaxHealth;
	int playerCurrentHealth;

	static const int MAX_BULLETS = 10;

	Bullet* bullets[MAX_BULLETS];	  //Move to Bullet.h

};

