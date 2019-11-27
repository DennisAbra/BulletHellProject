#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Boss.h"
class Collision;
class AudioManager;

class EntityManager
{
private:
	static EntityManager* instance;
	std::vector<Enemy*> enemies;

	Player* player;
	Boss* pepsiBoss;
	BossArm* bossArm;
	EntityManager();
	~EntityManager();

public:
	static EntityManager* Instance();
	void Release();

	void AddEnemies(Enemy* enemy);
	void AddPlayer(Player* _player);
	void AddBoss(Boss* boss);
	void AddBossArm(BossArm* bossArm);

	void Update();
	void Render();

};

