#pragma once
#include "GameEntity.h"
#include "EntityManager.h"

class ObjectPooling
{
	//TODO: Implement Enemy Reset
public:

	static ObjectPooling* instance; //Singleton

	int spawnTimer;

	ObjectPooling();
	~ObjectPooling();

	static ObjectPooling* Instance();

	void Release();

	void spawn(double x, double y, int lifeTime);

	void InitializeEnemyPool();

	void SetEnemyActive();

	void CleanUpEnemies();

	void SetEnemyInactive(int enemy);

	static const int POOL_SIZE = 5;

	Enemy* enemies[POOL_SIZE];
	//std::vector<Enemy*> enemies; Might want to use this instead


	

};
