#include "EntityManager.h"
#include "Collision.h"

EntityManager* EntityManager::instance = nullptr;

EntityManager* EntityManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new EntityManager();
	}

	return instance;
}

void EntityManager::Release()
{
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
	{
		delete* enemy;
	}
	enemies.clear();

	delete player;
	player = nullptr;

	delete instance;
	instance = nullptr;
}

void EntityManager::AddEnemies(Enemy* enemy) 
{
	enemies.push_back(enemy);
}

void EntityManager::AddPlayer(Player* _player)
{
	player = _player;
}

void EntityManager::Update()
{
	// SDL_Rect finalRect;
	//finalRect.w = player->texture->renderRect.w * 0.5;
	//finalRect.h = player->texture->renderRect.h * 0.5;
	for (auto enemy : enemies)
	{
		if (Collision::CheckAABBC(player->texture->renderRect, enemy->texture->renderRect))
		{
			Graphics::Instance()->DrawLine(enemy->texture->renderRect.x * 0.1, enemy->texture->renderRect.y * 0.1, enemy->texture->renderRect.x, enemy->texture->renderRect.y);
			player->OnCollision();
			if (!player->playerInvincible)
			{
				//printf("Collision With Player Detected!\n");
			}
		}
		else 
		{
			player->playerHit = false;
		}

		for (auto bullet : player->bullets)
		{
			if (Collision::CheckAABBC(bullet->texture->renderRect, enemy->texture->renderRect))
			{
				//printf("Collision with bullet detected!\n");
			}
		}
		enemy->Update();
	}
	
	player->Update();
}

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
}

void EntityManager::Render()
{
	for (auto enemy : enemies)
	{
		enemy->Render();
	}
	
	player->Render();
}
