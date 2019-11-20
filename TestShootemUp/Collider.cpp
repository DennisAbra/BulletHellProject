#include "Collider.h"

Collider::Collider(ColliderType type) : colliderType(type)
{
	debugTexture = nullptr;
}

Collider::~Collider()
{
	if (debugTexture)
	{
		delete debugTexture;
		debugTexture = nullptr;
	}
}

Collider::ColliderType Collider::GetColliderType()
{
	return colliderType;
}

void Collider::Render()
{
	if (DEBUG_COLLIDERS)
	{
		debugTexture->Render();
	}
}

void Collider::SetDebugTexture(Texture* tex)
{
	delete debugTexture;
	debugTexture = tex;
	debugTexture->Parent(this);
}
