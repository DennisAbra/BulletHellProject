#ifndef _BULLET_H
#define _BULLET_H
#include "PhysEntity.h"
#include "Timer.h"
#include "MathHelper.h"
#include "Graphics.h"

class Bullet : public PhysEntity 
{

private:

	const int OFFSCREEN_BUFFER = 10; //If offscreen by 10 pixels, disable bullet

	Timer* timer;
	
	float speed;

	bool IgnoreCollisions() override;
	bool friendlyBullet;

public:
	Texture* texture;
	Bullet(bool friendly);
	Bullet(bool friendly, std::string texturePath);
	~Bullet();

	void Fire(Vector2 pos);
	void Reload();

	void Hit(PhysEntity* other) override;

	void Update();
	void Render();


};


#endif