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

	if (friendly)
	{
		texture->Scale(Vector2(0.125f, 0.125f));
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

Bullet::Bullet(bool friendly, std::string texturePath)
{
	timer = Timer::Instance();

	speed = 750.0f;

	texture = new Texture(texturePath);
	texture->Parent(this);
	texture->Pos(Vec2_Zero);
	if (!friendly)
	{
		texture->Scale(Vector2(0.050f, 0.050f));
		speed = 350.0f;
	}

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

			///*Vector2 pos =*/ Pos();
		}
		else
		{
			Translate(Vec2_Up * speed * timer->DeltaTime());
			//TODO Check if it's a boss bullet. 
			// If true fire the bullet towards the player
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