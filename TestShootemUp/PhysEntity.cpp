#include "PhysEntity.h"
#include "PhysHelper.h"
#include "PhysManager.h"

PhysEntity::PhysEntity()
{
	broadPhaseCollider = nullptr;
	id = 0;
}

PhysEntity::~PhysEntity()
{
	for (int i = 0; i < colliders.size(); i++)
	{
		delete colliders[i];
		colliders[i] = nullptr;
	}
	colliders.clear();

	if (broadPhaseCollider)
	{
		delete broadPhaseCollider;
		broadPhaseCollider = nullptr;
	}

	if (id != 0)
	{
		PhysManager::Instance()->UnregisterEntity(id);
	}
}

unsigned long PhysEntity::GetId()
{
	return id;
}

bool PhysEntity::CheckCollision(PhysEntity* other)
{
	if (IgnoreCollisions() || other->IgnoreCollisions())
	{
		return false;
	}
	return ColliderColliderCheck(broadPhaseCollider, other->broadPhaseCollider);
}

void PhysEntity::Hit(PhysEntity* other)
{

}

void PhysEntity::Render()
{
	for (int i = 0; i < colliders.size(); i++)
	{
		colliders[i]->Render();
	}

	if (broadPhaseCollider)
	{
		broadPhaseCollider->Render();
	}
}

bool PhysEntity::IgnoreCollisions()
{
	return false;
}

void PhysEntity::AddCollider(Collider* col, Vector2 localPos)
{
	col->Parent(this);
	col->Pos(localPos);
	colliders.push_back(col);

	if (colliders.size() > 1 || 
		colliders[0]->GetColliderType() != Collider::ColliderType::Circle)
	{
		float furthestDistance = colliders[0]->GetFurthestPoint().Magnitude();
		float distance = 0.0f;
		for (int i = 1; i < colliders.size(); i++)
		{
			distance = colliders[i]->GetFurthestPoint().Magnitude();
			if (distance > furthestDistance)
			{
				furthestDistance = distance;
			}
		}

		delete broadPhaseCollider;
		broadPhaseCollider = new CircleCollider(furthestDistance, true);
		broadPhaseCollider->Parent(this);
		broadPhaseCollider->Pos(Vec2_Zero);
	}
}

