#include "CircleCollider.h"

CircleCollider::CircleCollider(float r, bool broadPhase)
	: Collider(ColliderType::Circle)
{
	radius = r;
	if (DEBUG_COLLIDERS)
	{
		if (broadPhase)
		{
			SetDebugTexture(new Texture("BroadPhaseCollider.png"));
		}
		else
		{
			SetDebugTexture(new Texture("CircleCollider.png"));
		}

		debugTexture->Scale(Vec2_One * (radius * 2 / 100.0f));
	}
}

CircleCollider::~CircleCollider()
{
}

Vector2 CircleCollider::GetFurthestPoint()
{
	return Vec2_Right * (radius + Pos(GameEntity::local).Magnitude());
}

float CircleCollider::GetRadius()
{
	return radius;
}
