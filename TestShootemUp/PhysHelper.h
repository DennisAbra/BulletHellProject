#pragma once
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "MathHelper.h"

inline bool CircleCircleCollision(CircleCollider* c1, CircleCollider* c2)
{
	return (c1->Pos() - c2->Pos()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}


inline bool ColliderColliderCheck(Collider* c1, Collider* c2)
{
	if (c1->GetColliderType() == Collider::ColliderType::Circle && c2->GetColliderType() == Collider::ColliderType::Circle)
	{
		return CircleCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	}
}