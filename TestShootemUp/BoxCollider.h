#pragma once
#include "Collider.h"


class BoxCollider : public Collider
{
private:
	static const int MAX_VERTS = 4;
	
	GameEntity* verts[MAX_VERTS];

	void AddVert(int index, Vector2 pos);

public:
	BoxCollider(Vector2 size);

	BoxCollider(Vector2 size, SDL_Point* pivotPoint);
	~BoxCollider();

	Vector2 GetFurthestPoint() override;

	Vector2 GetVertexPosition(int index);

};