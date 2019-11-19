#ifndef _BULLET_H
#define _BULLET_H
#include "Texture.h"
#include "Timer.h"
#include "MathHelper.h"
#include "Graphics.h"

class Bullet : public GameEntity 
{

private:

	const int OFFSCREEN_BUFFER = 10; //If offscreen by 10 pixels, disable bullet

	Timer* timer;
	
	float speed;

	Texture* texture;

public:

	Bullet();
	~Bullet();

	void Fire(Vector2 pos);
	void Reload();

	void Update();
	void Render();


};


#endif