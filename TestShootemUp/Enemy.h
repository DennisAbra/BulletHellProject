#pragma once
#include "GameEntity.h"


class Enemy : public GameEntity
{
private:
	Enemy();
	~Enemy();

public:
	void Render();
};


