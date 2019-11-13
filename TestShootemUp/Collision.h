#pragma once
#include <SDL_rect.h>

class Collision
{
public:
	//AABC - axis aligned box bounds collision or something of the sorts
	static bool CheckAABBC(const SDL_Rect& a, const SDL_Rect& b);

private:
	Collision() {}
	Collision(const Collision& oter) { }
	~Collision() {}
};

