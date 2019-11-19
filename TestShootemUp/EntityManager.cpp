#include "EntityManager.h"

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
	for (auto enemy : enemies)
	{
		//TODO - create a kongo line of enemies
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
