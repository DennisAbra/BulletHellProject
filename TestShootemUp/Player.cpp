#include "Player.h"
#include <iostream>

Player::Player(int posX, int posY, InputManager* input, const char* filePath) : input(input)
{
	playerHit = false;
	gameOver = false;
	gameOverDelay = 6.0f;
	gameOverTimer = 0.0f;

	invincibilityFrameTimer = maxInvincibilityFrameTimer;
	currentState = alive;

	position.x = posX;
	position.y = posY;

	texture = new Texture(filePath);
	texture->Pos(position);

	playerCurrentHealth = playerMaxHealth;

	movementState = MovementStates::KEYBOARD;

	timer = timer->Instance();

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i] = new Bullet();
	}
}

Player::~Player()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete bullets[i];
		bullets[i] = nullptr;
	}
}

void Player::WasHit()
{
	printf("Player current HP:%i ", playerCurrentHealth);
	if (!playerInvincible)
	{
		playerCurrentHealth--;
	}
}

void Player::Invincible()
{
	invincibilityFrameTimer -= timer->DeltaTime();
	/*printf("Invincibility Frame Timer: %f\n", invincibilityFrameTimer);*/
	if (invincibilityFrameTimer <= 0.0f)
	{
		printf("Invincibility false: %f\n", invincibilityFrameTimer);
		playerInvincible = false;

		if (!playerInvincible)
		{
			invincibilityFrameTimer = maxInvincibilityFrameTimer;
		}
	}
}

void Player::OnCollision()
{
	WasHit();
	playerInvincible = true;
}

void Player::HandlePlayerDeath()
{
	if (playerCurrentHealth <= 0 && !playerInvincible)
	{
		Active(false); //Player is "dead"
	}
}

void Player::Update()
{
	//printf("Player invincible: %b", playerInvincible);
	

	if (playerInvincible)
	{

		Invincible();
	}

	if (playerCurrentHealth <= 0)
	{
		HandlePlayerDeath();
	}

	SwitchMovement();
	MovePlayer();
	texture->Pos(position);

	firePoint = { texture->Pos().x, texture->Pos().y - 20 };

	HandleFiring();

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i]->Update();
	}
}

void Player::Render()
{
	if (Active())
	{
		texture->Render();
	}
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i]->Render();
	}
}

void Player::HandleFiring()
{
	if (input->KeyPressed(SDL_SCANCODE_SPACE))
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!bullets[i]->Active())
			{
				bullets[i]->Fire(firePoint);
			}
		}
	}
}

void Player::handlePlayerStates()
{
	switch (currentState)
	{
	case alive:
		active = true;
		break;

	case dead:
		active = false;
		break;
	}
}

void Player::handleAliveState()
{
	//Check HP
	this->active = true; //Expand later.
}

void Player::handleDeadState()
{
	//Play death animation.
	this->active = false; //Inactivate player
	//Check if player wants to restart
}

bool Player::ShouldNormalizeVector()
{
	if (input->KeyDown(SDL_SCANCODE_W) && input->KeyDown(SDL_SCANCODE_D)
		|| input->KeyDown(SDL_SCANCODE_W) && input->KeyDown(SDL_SCANCODE_A)
		|| input->KeyDown(SDL_SCANCODE_S) && input->KeyDown(SDL_SCANCODE_A)
		|| input->KeyDown(SDL_SCANCODE_S) && input->KeyDown(SDL_SCANCODE_D))
	{
		return true;
	}
	return false;
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
				position.y = 0 + texture->GetHeight() * .5f;
			}
			movement.y -= 10;
		}

		if (input->KeyDown(SDL_SCANCODE_S))
		{
			if (position.y >= Graphics::screenHeight - texture->GetHeight() * .5f)
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
		if (ShouldNormalizeVector())
		{
			position += (movement * .75f) * speed * timer->DeltaTime();
		}
		else
		{
			position += movement * speed * timer->DeltaTime();
		}

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


