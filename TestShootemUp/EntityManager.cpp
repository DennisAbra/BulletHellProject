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

	//TODO : does this work or create memory leak?
	delete player;
	player = nullptr;

	delete instance;
	instance = nullptr;
}

void EntityManager::AddEnemies(Enemy* enemy) //TODO: Decide with group if we remove these or implement object pooling in this script/GameEntity instead instead?
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
		//TODO - create a kongo line of enemies
		if (Collision::CheckAABBC(player->texture->renderRect, enemy->texture->renderRect))
		{
			Graphics::Instance()->DrawLine(enemy->texture->renderRect.x * 0.1, enemy->texture->renderRect.y * 0.1, enemy->texture->renderRect.x, enemy->texture->renderRect.y);
			//printf("WE HAVE COLLIDED GOOD SIR\n");
		}

		for (auto bullet : player->bullets)
		{
			if (Collision::CheckAABBC(bullet->texture->renderRect, enemy->texture->renderRect))
			{
				printf("Bullet collided \n");
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
