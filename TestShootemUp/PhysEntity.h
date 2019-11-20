#pragma once
#include "Collider.h"
#include <vector>


class PhysEntity : public GameEntity
{
protected:
	unsigned long id;
	std::vector<Collider*> colliders;
	Collider* broadPhaseCollider;

	virtual bool IgnoreCollisions();
	void AddCollider(Collider* col, Vector2 localPos = Vec2_Zero);

public:
	PhysEntity();
	virtual ~PhysEntity();

	unsigned long GetId();

	bool CheckCollision(PhysEntity* other);

	virtual void Hit(PhysEntity* other);

	virtual void Render();
};