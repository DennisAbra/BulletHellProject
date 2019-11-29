#pragma once
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "MathHelper.h"

inline bool PointInPolygon(Vector2* verts, int vertCount, const Vector2& point)
{
	bool returnValue = false;

	for (int i = 0, j = vertCount - 1; i < vertCount; j = i++)
	{
		if ((verts[i].y >= point.y) != (verts[j].y >= point.y))
		{
			Vector2 vec1 = (verts[i] - verts[j]).Normalized();
			Vector2 projection = verts[j] + vec1 * Dot(point - verts[j], vec1);
			if (projection.x > point.x)
			{
				returnValue = !returnValue;
			}
		}
	}

	return returnValue;
}

inline float PointToLineDistance(const Vector2& lineStart, const Vector2& lineEnd, const Vector2& point)
{
	Vector2 slope = lineEnd - lineStart;

	float param = Clamp(Dot(point - lineStart, slope) / slope.MagnitudeSqr(), 0.0f, 1.0f);

	Vector2 nearestPoint = lineStart + slope * param;

	return (point - nearestPoint).Magnitude();
}

inline bool CircleCircleCollision(CircleCollider* c1, CircleCollider* c2)
{
	return (c1->Pos() - c2->Pos()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool BoxCircleCollision(BoxCollider* box, CircleCollider* circle)
{
	Vector2 quad[4];
	quad[0] = box->GetVertexPosition(0);
	quad[1] = box->GetVertexPosition(1);
	quad[2] = box->GetVertexPosition(3);
	quad[3] = box->GetVertexPosition(2);

	float radius = circle->GetRadius();
	Vector2 circlePos = circle->Pos();

	for (int i = 0; i < 4; i++)
	{
		if ((quad[i] - circlePos).Magnitude() < radius)
		{
			return true;
		}
	}

	if (PointToLineDistance(box->GetVertexPosition(0), box->GetVertexPosition(1), circlePos) < radius
		|| PointToLineDistance(box->GetVertexPosition(0), box->GetVertexPosition(2), circlePos) < radius
		|| PointToLineDistance(box->GetVertexPosition(2), box->GetVertexPosition(3), circlePos) < radius
		|| PointToLineDistance(box->GetVertexPosition(3), box->GetVertexPosition(1), circlePos) < radius)
	{
		return true;
	}

	if (PointInPolygon(quad, 4, circlePos))
	{
		return true;
	}

	return false;
}


inline bool ColliderColliderCheck(Collider* c1, Collider* c2)
{
	if (c1->GetColliderType() == Collider::ColliderType::Circle && c2->GetColliderType() == Collider::ColliderType::Circle)
	{
		return CircleCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	}
	else if (c1->GetColliderType() == Collider::ColliderType::Box && c2->GetColliderType() == Collider::ColliderType::Circle)
	{
		return BoxCircleCollision(static_cast<BoxCollider*>(c1), static_cast<CircleCollider*> (c2));
	}
	else if (c2->GetColliderType() == Collider::ColliderType::Box && c1->GetColliderType() == Collider::ColliderType::Circle)
	{
		return BoxCircleCollision(static_cast<BoxCollider*>(c2), static_cast<CircleCollider*> (c1));
	}

}