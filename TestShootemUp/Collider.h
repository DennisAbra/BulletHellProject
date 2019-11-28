#pragma once
#include "Texture.h"


class Collider : public GameEntity
{
public:
	enum class ColliderType
	{
		Box,
		Circle
	};

	Collider(ColliderType type);
	virtual ~Collider();;

	virtual Vector2 GetFurthestPoint() = 0;

	ColliderType GetColliderType();

	virtual void Render();


protected:
	ColliderType colliderType;

	static const bool DEBUG_COLLIDERS = true;
	Texture* debugTexture;

	void SetDebugTexture(Texture* tex);
};