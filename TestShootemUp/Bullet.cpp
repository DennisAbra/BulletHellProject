#include "Bullet.h"

Bullet::Bullet() 
{
	timer = Timer::Instance();

	speed = 500.0f;

	texture = new Texture("Bubble4.png");
	texture->Parent(this);
	texture->Pos(Vec2_Zero);

	Reload();
}

Bullet::~Bullet() 
{
	timer = NULL;

	delete texture;
    
	texture = NULL;
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
	}
}