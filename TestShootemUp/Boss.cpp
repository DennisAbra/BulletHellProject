#include "Boss.h"



Boss::Boss(int path) : Enemy(path)
{
}

Boss::Boss(int path, std::string textureName)
:Enemy(path,textureName)
{
	
}

Boss::~Boss()
{
	delete texture;
	texture = nullptr;
}






