#pragma once
#include "GameEntity.h"
#include "EntityManager.h"
#include <string>
#include "Timer.h"
#include <vector>

class ObjectPooling
{
private:

	static ObjectPooling* Instance; //Singleton

public:

	int spawnTimer;

	ObjectPooling();
	~ObjectPooling();


	void spawn(double x, double y, int lifeTime);

	void CleanUpEnemies(); //Not implemented in cpp
	void CleanUpBullets(); //Not implemented in cpp

	GameEntity SpawnAfterTime(float spawnTime, std::string object);

	void animate();

private:

	static const int POOL_SIZE = 2;
};
