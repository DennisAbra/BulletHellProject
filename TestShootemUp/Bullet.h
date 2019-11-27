#ifndef _BULLET_H
#define _BULLET_H
#include "PhysEntity.h"
#include "Timer.h"
#include "MathHelper.h"
#include "Graphics.h"

class Player;

class Bullet : public PhysEntity 
{

private:

	 Player* bulletsPlayerRef;

	Timer* timer;
	
	float speed;

	bool IgnoreCollisions() override;
	bool friendlyBullet;

public:
	enum Type
	{
		Friendly,
		Enemy,
		Boss
	};

	Type type;

	const int OFFSCREEN_BUFFER = 10; //If offscreen by 10 pixels, disable bullet
	Texture* texture;
	Bullet(bool friendly);
	Bullet(Type typeShootingTheBullet, std::string texturePath);
	~Bullet();

	void Fire(Vector2 pos);
	void Reload();

	void GetPlayer(Player* myPlayer);

	void Hit(PhysEntity* other) override;

	void Update();
	void Render();


};


#endif