#include "ObjectPooling.h"
#include "Enemy.h"

ObjectPooling* ObjectPooling::instance = nullptr;

ObjectPooling* ObjectPooling::Instance()
{
	if (instance == nullptr)
	{
		instance = new ObjectPooling();
	}

	return instance;
}

void ObjectPooling::Release()
{
	delete instance;
	instance = nullptr;

	//CleanUpEnemies();
}

ObjectPooling::ObjectPooling() //cTor
{
}

ObjectPooling::~ObjectPooling()
{
}

/* Create Enemies store them in enemies[] and set them to inactive*/
void ObjectPooling::InitializeEnemyPool()
{
	for (int i = 0; i < POOL_SIZE / 3; i++)
	{
		enemies[i] = new Enemy(0);
	}
	for (int i = 5; i < 10; i++)
	{
		enemies[i] = new Enemy(1);
	}

	for (int i = 10; i < POOL_SIZE; i++)
	{
		enemies[i] = new Enemy(2);
	}
}

void ObjectPooling::SetEnemyActive() // Sets all enemies active. Think about the nameing of this method. Possibly change it to only make a specific enemy active
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		enemies[i]->active = true;
	}
}

/* Deletes all enemies created */
void ObjectPooling::CleanUpEnemies()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		enemies[i]->active = false;
		enemies[i] = nullptr;
		delete enemies[i];
	}
	
	// if using std::vector<Enemy*>
	//enemies.clear();
}

void ObjectPooling::SetEnemyInactive(int enemy)// Sets all enemies active. Think about the nameing of this method. Possibly change it to only make a specific enemy inactive
{
	enemies[enemy]->active = false;
}

//std::vector<Enemy*> ObjectPooling::GetListOfEnemies()
//{
//	return enemies;
//}




