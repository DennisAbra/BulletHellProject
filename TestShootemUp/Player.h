#pragma once
#include "GameEntity.h"
#include "InputManager.h"
#include "Texture.h"
#include "Timer.h"
#include "Bullet.h"

class Bullet;

class Player : public GameEntity
{
public:

	Player(int posX, int posY, InputManager* input, const char* filePath);
	~Player();
	void Update();
	void Render();

	enum class  MovementStates { KEYBOARD = 0, MOUSE = 1 };
	

private:
	void HandleFiring();
private:


	Bullet* bullet;
	InputManager* input;
	Texture* texture;

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

	static const int MAX_BULLETS = 2;
	Bullet* bullets[MAX_BULLETS];
};

