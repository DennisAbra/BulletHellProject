#include "Boss.h"
#include "BoxCollider.h"
#include "PhysManager.h"

Boss::Boss(int path) : Enemy(path)
{
}

Boss::Boss(int path, std::string textureName)
:Enemy(path,textureName)
{
	AddCollider(new BoxCollider(Vector2(150, 150)));
	id = PhysManager::Instance()->RegisterEntity(this, PhysManager::CollisionLayers::Hostile);
}

Boss::~Boss()
{
	delete texture;
	texture = nullptr;
}






