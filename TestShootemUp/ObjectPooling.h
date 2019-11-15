#pragma once
#include "GameEntity.h"
#include <string>
#include "Timer.h"
#include <vector>

class ObjectPooling
{
private:

	GameEntity* enemy = new GameEntity;
	GameEntity* bullet = new GameEntity;

	static ObjectPooling* Instance; //Singleton

public:

	int spawnTimer;
	ObjectPooling();
	~ObjectPooling();
	void spawn(double x, double y, int lifeTime);

	GameEntity SpawnAfterTime(float spawnTime, std::string object);

	void animate();

private:

	static const int POOL_SIZE = 2;
	GameEntity entities[POOL_SIZE]; //Array of game entities for spawning, might convert to List later.
};
