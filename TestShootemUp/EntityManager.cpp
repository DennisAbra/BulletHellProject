#include "EntityManager.h"
#include "Collision.h"
#include "AudioManager.h"

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

	delete bossArm;
	bossArm = nullptr;

	delete pepsiBoss;
	pepsiBoss = nullptr;

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

void EntityManager::AddBoss(Boss* boss)
{
	pepsiBoss = boss;
}

void EntityManager::AddBossArm(BossArm* bossArm)
{
	this->bossArm = bossArm;
}

void EntityManager::Update()
{
	for (auto enemy : enemies)
	{

		Graphics::Instance()->DrawLine(enemy->texture->renderRect.x * 0.1, enemy->texture->renderRect.y * 0.1, enemy->texture->renderRect.x, enemy->texture->renderRect.y);

		if (player->WasHit())
		{
			player->playerInvincible = true;
		}

		if (enemy->WasHit())
		{
			enemy->invincible = true;
		}

		

		enemy->Update();
	}

	if (Enemy::bossSpawned)
	{
		pepsiBoss->Update();
		bossArm->Update();
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
	if (Enemy::bossSpawned)
	{
		pepsiBoss->Render();
		bossArm->Render();
	}

	player->Render();
	player->emptyGlass->Render();

	if (player->glassBottom->active == true) 
	{
		player->glassBottom->Render();
	}
	if (player->glassMiddle->active == true) 
	{
		player->glassMiddle->Render();
	}
	if (player->glassTop->active == true) 
	{
		player->glassTop->Render();
	}
	
}
