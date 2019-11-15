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

bool Player::CheckMouseScreenBounds()
{
	if (position.x <= 0 + texture->GetWidth() * .5f && input->MousePos().x <= 0 + texture->GetWidth() * .5f)
	{
		return false;
	}
	if (position.x >= Graphics::screenWidth - texture->GetWidth() * .5f && input->MousePos().x >= Graphics::screenWidth - texture->GetWidth() * .5f)
	{
		return false;
	}
	if (position.y >= Graphics::screenHeight - texture->GetHeight() * .5f && input->MousePos().y >= Graphics::screenHeight - texture->GetHeight() * .5f)
	{
		return false;
	}
	if (position.y <= 0 + texture->GetHeight() * .5f && input->MousePos().y <= 0 + texture->GetHeight() * .5f)
	{
		return false;
	}
	return true;
}


void Player::MovePlayer()
{
	
	if (movementState == MovementStates::KEYBOARD)
	{
		Vector2 movement;
		if (input->KeyDown(SDL_SCANCODE_W))
		{
			if (position.y <= 0 + texture->GetHeight() * .5f)
			{
				position.y =  0 + texture->GetHeight() * .5f;
			}
			movement.y -= 10;
		}
		if (input->KeyDown(SDL_SCANCODE_S))
		{
			if (position.y >= Graphics::screenHeight - texture->GetHeight()* .5f)
			{
				position.y = Graphics::screenHeight - texture->GetHeight() * .5f;
			}
			movement.y += 10;
		}
		if (input->KeyDown(SDL_SCANCODE_A))
		{
			if (position.x <= 0 + texture->GetWidth() * .5f)
			{
				position.x = 0 + texture->GetWidth() * .5f;
			}
			movement.x -= 10;
		}
		if (input->KeyDown(SDL_SCANCODE_D))
		{
			if (position.x >= Graphics::screenWidth - texture->GetWidth() * .5f)
			{
				position.x = Graphics::screenWidth - texture->GetWidth() * .5f;
			}
			movement.x += 10;
		}
		position += movement * speed * timer->DeltaTime();
	}
	else if (movementState == MovementStates::MOUSE)
	{
		if (!CheckMouseScreenBounds())
		{
			return;
		}
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


