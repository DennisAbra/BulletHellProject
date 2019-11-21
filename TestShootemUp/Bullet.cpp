#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysManager.h"

Bullet::Bullet(bool friendly)
{
	timer = Timer::Instance();

	speed = 750.0f;

	texture = new Texture("PlayerBullet.png");
	texture->Parent(this);
	texture->Pos(Vec2_Zero);
	texture->Scale(Vector2(0.125f, 0.125f));

	Reload();

	AddCollider(new BoxCollider(texture->ScaledDimensions()));
	if (friendly)
	{
		PhysManager::Instance()->RegisterEntity(this, PhysManager::CollisionLayers::FriendlyProjectile);
	}
	else
	{
		PhysManager::Instance()->RegisterEntity(this, PhysManager::CollisionLayers::HostileProjectile);
	}
}

Bullet::~Bullet() 
{
	timer = nullptr;

	delete texture;
    
	texture = nullptr;
}

void Bullet::Fire(Vector2 pos) 
{
	Pos(pos);
	Active(true);
}

void Bullet::Reload() 
{
	Active(false);

	Pos(Graphics::screenHeight + 100);
}

void Bullet::Hit(PhysEntity* other)
{
	printf("You have the the rubber ducky\n");
	Reload();
}

bool Bullet::IgnoreCollisions()
{
	return !Active();
}

void Bullet::Update() 
{
	if (Active()) 
	{
		Translate(Vec2_Down * speed * timer->DeltaTime());

		Vector2 pos = Pos();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->screenHeight + OFFSCREEN_BUFFER)
		{
			Reload();
		}
	}
}

void Bullet::Render() 
{
	if (Active()) 
	{
		texture->Render();
		PhysEntity::Render();
	}
}