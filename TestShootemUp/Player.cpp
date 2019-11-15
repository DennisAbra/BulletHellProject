#include "Player.h"

Player::Player(int posX, int posY, InputManager* input) : input(input)
{
	position.x = posX;
	position.y = posY;
}

void Player::Update()
{
}

void Player::Render()
{
}

void Player::MovePlayer()
{
	Player::SwitchMovement();
	if (movementState == KEYBOARD)
	{
		if (input->KeyPressed(SDL_SCANCODE_W))
		{
			position.y -= 10;
		}
		else if (input->KeyPressed(SDL_SCANCODE_S))
		{
			position.y += 10;
		}
		else if (input->KeyPressed(SDL_SCANCODE_A))
		{
			position.x -= 10;
		}
		else if (input->KeyPressed(SDL_SCANCODE_D))
		{
			position.x += 10;
		}
	}
	else if (movementState == MOUSE)
	{
		position = input->MousePos();
	}
	
}

void Player::SwitchMovement()
{
	if (movementState == KEYBOARD)
	{
		if (input->middle)
		{
			movementState = MOUSE;
		}
	}
	else if (movementState == MOUSE)
	{
		if (input->middle)
		{
			movementState = KEYBOARD;
		}
	}
}


