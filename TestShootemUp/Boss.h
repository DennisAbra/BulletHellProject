#pragma once
#include "Enemy.h"
#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "ObjectPooling.h"
#include "BossArm.h"

class Boss : public Enemy
{
private:



public:
	//Texture* texture;

	//Vector2 startPos;

	Boss(int path);
	Boss(int path, std::string textureName);
	virtual ~Boss();




	


};

