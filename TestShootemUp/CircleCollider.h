#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
private:
	float radius;

public:
	CircleCollider(float r, bool broadPhase = false);
	~CircleCollider();

	Vector2 GetFurthestPoint() override;
	float GetRadius();
};