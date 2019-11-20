#include "Bullet.h"

Bullet::Bullet() 
{
	timer = Timer::Instance();

	speed = 750.0f;

	texture = new Texture("Bubble4.png");
	texture->Parent(this);
	texture->Pos(Vec2_Zero);
	texture->Scale(Vector2(0.5f, 0.5f));

	Reload();
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