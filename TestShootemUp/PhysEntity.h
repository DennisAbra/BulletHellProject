#pragma once
#include "Collider.h"
#include <vector>


class PhysEntity : public GameEntity
{
protected:
	void AddCollider(Collider* col, Vector2 localPos = Vec2_Zero);
	unsigned long id;
	std::vector<Collider*> colliders;
	Collider* broadPhaseCollider;

	virtual bool IgnoreCollisions();


public:
	PhysEntity();
	virtual ~PhysEntity();

	unsigned long GetId();

	bool CheckCollision(PhysEntity* other);

	virtual void Hit(PhysEntity* other);

	virtual void Render();
};