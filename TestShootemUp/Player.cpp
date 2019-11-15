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
	if (currentState == KEYBOARD)
	{
		if (input.)
		{

		}
	}
	else if (currentState == MOUSE)
	{
		position = input->MousePos();
	}
	
}

void Player::SwitchMovement()
{
	if (currentState == KEYBOARD)
	{
		if (input->middle)
		{
			currentState = MOUSE;
		}
	}
	else if (currentState == MOUSE)
	{
		if (input->middle)
		{
			currentState = KEYBOARD;
		}
	}
}


