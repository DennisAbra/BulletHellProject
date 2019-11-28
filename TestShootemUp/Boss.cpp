#include "Boss.h"
#include "CircleCollider.h"
#include "PhysManager.h"

void Boss::Hit(PhysEntity* other)
{
	if (!invincible && !BossArm::armIsAlive)
	{
		invincible = true;
		health--;
		wasHit = true;
	}
}

Boss::Boss(int path) : Enemy(path)
{
}

Boss::Boss(int path, std::string textureName, Player* player)
:Enemy(path,textureName, player)
{
	health = 10;
	maxHealth = 10;

	AddCollider(new CircleCollider(100));
	speed = 100.f;
	id = PhysManager::Instance()->RegisterEntity(this, PhysManager::CollisionLayers::Hostile);
}

Boss::~Boss()
{
	delete texture;
	texture = nullptr;
}

void Boss::HandleFlyInState()
{
	if ((paths[currentPath][currentWaypoint] - Pos()).MagnitudeSqr() < epsilon)
	{
		currentWaypoint++;
	}

	if (currentWaypoint < paths[currentPath].size())
	{
		Vector2 distance = paths[currentPath][currentWaypoint] - Pos();
		Translate(distance.Normalized() * timer->DeltaTime() * speed);
	}
	else
	{
		currentWaypoint = 45;
	}
}






