#pragma once
#include "Enemy.h"
#include "Player.h"


class EntityManager
{
private:
	static EntityManager* instance;
	std::vector<Enemy*> enemies;

	Player* player;

	EntityManager();
	~EntityManager();


public:
	static EntityManager* Instance();
	void Release();

	void AddEnemies(Enemy* enemy);
	void AddPlayer(Player* _player);

	void Update();
	void Render();

};

