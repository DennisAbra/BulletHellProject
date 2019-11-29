#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysManager.h"
#include "Player.h"

Bullet::Bullet(bool friendly)
{
	timer = Timer::Instance();

	speed = 750.0f;

	texture = new Texture("PlayerBullet.png");
	texture->Parent(this);
	texture->Pos(Vec2_Zero);

	if (friendly)
	{
		texture->Scale(Vector2(0.25f, 0.25f));
	}


	Reload();
	friendlyBullet = friendly;
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

Bullet::Bullet(Type typeShootingTheBullet, std::string texturePath)
{
	timer = Timer::Instance();

	speed = 750.0f;

	texture = new Texture(texturePath);
	texture->Parent(this);
	texture->Pos(Vec2_Zero);
	if (typeShootingTheBullet == Bullet::Enemy)
	{
		texture->Scale(Vector2(0.050f, 0.050f));
		speed = 350.0f;
	}
	else if (typeShootingTheBullet == Bullet::Boss)
	{
		texture->Scale(Vector2(0.5f, 0.5f));
		speed = 350.0f;
	}

	Reload();

	AddCollider(new BoxCollider(texture->ScaledDimensions()));
	if (Bullet::Friendly)
	{
		PhysManager::Instance()->RegisterEntity(this, PhysManager::CollisionLayers::FriendlyProjectile);
	}
	else 
	{
		PhysManager::Instance()->RegisterEntity(this, PhysManager::CollisionLayers::HostileProjectile);
	}
	type = typeShootingTheBullet;
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
}

void Bullet::GetPlayer(Player* myPlayer)
{
	bulletsPlayerRef = myPlayer;
}


void Bullet::Hit(PhysEntity* other)
{
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
		if (friendlyBullet)
		{
			Translate(Vec2_Down * speed * timer->DeltaTime());
		}
		else if(type == Enemy)
		{
			Translate(Vec2_Up * speed * timer->DeltaTime());
		}

		if (Pos().y < -OFFSCREEN_BUFFER || Pos().y > Graphics::screenHeight + OFFSCREEN_BUFFER || Pos().x < -OFFSCREEN_BUFFER || Pos().x > Graphics::screenWidth + OFFSCREEN_BUFFER)
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