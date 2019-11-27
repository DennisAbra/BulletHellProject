#include "BoxCollider.h"



BoxCollider::BoxCollider(Vector2 size) : Collider(ColliderType::Box)
{
	AddVert(0, Vector2(-0.5 * size.x, -0.5f * size.y));
	AddVert(1, Vector2(0.5 * size.x, -0.5f * size.y));
	AddVert(2, Vector2(-0.5 * size.x, 0.5f * size.y));
	AddVert(3, Vector2(0.5 * size.x, 0.5f * size.y));

	if (DEBUG_COLLIDERS)
	{
		SetDebugTexture(new Texture("DebugCollider.png"));
		debugTexture->Scale(size / 100.0f);
	}
}



BoxCollider::BoxCollider(Vector2 size, SDL_Point* pivotPoint) : Collider(ColliderType::Box)
{
	AddVert(0, Vector2(-0.5 * size.x, -0.5f * size.y));
	AddVert(1, Vector2(0.5 * size.x, -0.5f * size.y));
	AddVert(2, Vector2(-0.5 * size.x, 0.5f * size.y));
	AddVert(3, Vector2(0.5 * size.x, 0.5f * size.y));

	if (DEBUG_COLLIDERS)
	{
		SetDebugTexture(new Texture("DebugCollider.png",pivotPoint));
		debugTexture->Scale(size / 100.0f);
	}
}

BoxCollider::~BoxCollider()
{
	for (int i = 0; i < MAX_VERTS; i++)
	{
		delete verts[i];
		verts[i] = nullptr;
	}
}

Vector2 BoxCollider::GetFurthestPoint()
{
	Vector2 localPos = Pos(GameEntity::local);
	int furthestIndex = 0;
	float distance = (localPos + verts[0]->Pos(GameEntity::local)).MagnitudeSqr();

	float otherDistance = 0.0f;

	for (int i = 1; i < MAX_VERTS; i++)
	{
		otherDistance = (localPos + verts[i]->Pos(GameEntity::local)).MagnitudeSqr();
		if (otherDistance > distance)
		{
			furthestIndex = i;
			distance = otherDistance;
		}
	}

	return localPos + verts[furthestIndex]->Pos(GameEntity::local);
}

Vector2 BoxCollider::GetVertexPosition(int index)
{
	return verts[index]->Pos();
}

void BoxCollider::AddVert(int index, Vector2 pos)
{
	verts[index] = new GameEntity(pos.x, pos.y);
	verts[index]->Parent(this);
}
