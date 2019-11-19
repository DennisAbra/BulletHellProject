#pragma once
#include "GameEntity.h"

class Enemy;

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

	void Spawn(double x, double y, int lifeTime);

	void InitializeEnemyPool();

	void SetEnemyActive();

	void CleanUpEnemies();

	void SetEnemyInactive(int enemy);

	//std::vector<Enemy*> GetListOfEnemies();

	static const int POOL_SIZE = 15;

	Enemy* enemies[POOL_SIZE];
	//std::vector<Enemy*> enemies; //Might want to use this instead


	

};
