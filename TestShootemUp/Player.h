#pragma once
#include "GameEntity.h"
#include "InputManager.h"

class Player : public GameEntity
{
public:
	Player(int posX, int posY, InputManager* input);

	void Update();
	void Render();

	enum MovementStates {KEYBOARD = 0, MOUSE};
	
private:
	InputManager* input;

	Vector2 position;
	Vector2 scale;

	float rotation;

	bool active;
	bool mouseMovement;

	MovementStates movementState;
	
	void MovePlayer();
	void SwitchMovement();
};

