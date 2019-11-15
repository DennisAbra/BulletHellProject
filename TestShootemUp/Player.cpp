#include "Player.h"

Player::Player(int posX, int posY, InputManager* input, const char* filePath) : input(input)
{
	position.x = posX;
	position.y = posY;

	texture = new Texture(filePath);
	texture->Pos(position);

	movementState = MovementStates::KEYBOARD;

	timer = timer->Instance();
}

void Player::Update()
{
	SwitchMovement();
	MovePlayer();
	texture->Pos(position);
	
}

void Player::Render()
{
	if (Active())
	{
		texture->Render();
	}
}

void Player::MovePlayer()
{
	
	if (movementState == MovementStates::KEYBOARD)
	{
		Vector2 movement;
		if (input->KeyDown(SDL_SCANCODE_W))
		{
			movement.y -= 10;
		}
		if (input->KeyDown(SDL_SCANCODE_S))
		{
			movement.y += 10;
		}
		if (input->KeyDown(SDL_SCANCODE_A))
		{
			movement.x -= 10;
		}
		if (input->KeyDown(SDL_SCANCODE_D))
		{
			movement.x += 10;
		}
		position += movement * speed * timer->DeltaTime();
	}
	else if (movementState == MovementStates::MOUSE)
	{
		position = input->MousePos();
	}
	
}

void Player::SwitchMovement()
{
	if (movementState == MovementStates::KEYBOARD && input->MouseButtonReleased(InputManager::Mouse_Button::middle))
	{
			movementState = MovementStates::MOUSE;		
	}
	else if (movementState == MovementStates::MOUSE && input->MouseButtonReleased(InputManager::Mouse_Button::middle))
	{		
			movementState = MovementStates::KEYBOARD;		
	}
}


