#include "Collision.h"

bool Collision::CheckAABBC(const SDL_Rect& a, const SDL_Rect& b)
{
	if (a.x + a.w >= b.x &&
		b.x + b.w >= a.x &&
		a.y + a.h >= b.y &&
		b.y + b.h >= a.y)
	{
		return true; // We have collided
	}
	return false;
}
