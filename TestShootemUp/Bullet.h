#pragma once
#include <vector>
#include "AnimatedTexture.h"

class Bullet
{
public:
	std::vector<Bullet*> bullets;
	void PlayerShoot(Vector2 position);

private:
	int offsetX;
	int offsetY;
};

