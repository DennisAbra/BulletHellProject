#pragma once
#include "GameEntity.h"
#include "InputManager.h"
#include "Texture.h"
#include "Timer.h"
class Player : public GameEntity
{
public:
	Player(int posX, int posY, InputManager* input, const char* filePath);

	void Update();
	void Render();

	enum class  MovementStates { KEYBOARD = 0, MOUSE = 1 };
	
private:
	InputManager* input;
	Texture* texture;

	Vector2 position;
	Vector2 scale;

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
};

