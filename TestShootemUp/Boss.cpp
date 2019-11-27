#include "Boss.h"
#include "BoxCollider.h"
#include "PhysManager.h"

Boss::Boss(int path) : Enemy(path)
{
}

Boss::Boss(int path, std::string textureName, Player* player)
:Enemy(path,textureName, player)
{
	AddCollider(new BoxCollider(Vector2(150, 150)));

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

		//Rotation(atan2(distance.y, distance.x) * radToDeg);
	}
	else
	{
		currentWaypoint = 1;
	}
}






