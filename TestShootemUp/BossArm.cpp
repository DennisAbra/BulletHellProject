#include "BossArm.h"
#include "BoxCollider.h"
#include "PhysManager.h"


BossArm::BossArm(int path, std::string textureName, Player* player) : Enemy(path, textureName, NULL)
{

}

BossArm::BossArm(int path, std::string textureName, InputManager* input, Player* _player) : Enemy(path, textureName, _player), input(input)
{
	speed = 100.f;
	posOffset = Vector2(110, 50);
	AddCollider(new BoxCollider(texture->ScaledDimensions() * 0.5f, &point));

	timer = Timer::Instance();

	currentPath = path;

	currentState = flyIn;
	
	currentWaypoint = 0;
	Pos(paths[currentPath][currentWaypoint]);

	texture = new Texture(textureName, &point);
	texture->Parent(this);

	texture->Pos(Vec2_Zero);

	health = 10;
	maxHealth = 10;

	player = _player;

	firePointEntity = new GameEntity();
	firePointEntity->Parent(this);
	firePointEntity->Pos(Vec2_Zero);
	firePointEntity->Pos(Vector2(25, 60));
}

BossArm::~BossArm()
{
	delete firePointEntity;
	firePointEntity = nullptr;
	player = nullptr;

	input = nullptr;
}


void BossArm::AimTowardsPlayer(Player* player)
{
	this->player = player;
	distanceToPlayer = this->Pos() - player->Pos();
	rotation = atan2(distanceToPlayer.y, distanceToPlayer.x) * radToDeg + 90.f;
	if (rotation < 35 && rotation > -55)
	{
		Rotation(rotation);
	}
}


void BossArm::Update()
{
	if (Parent()->Active())
	{
		if (invincible)
		{
			Invincible();
		}

		if (health <= 0)
		{
			isAlive = false; //TODO Change this to a bool - isAlive // What are you talking about, this is a bool??
		}

		static float time;
		static float t = 2.0f;
		time += timer->DeltaTime();

		if (Active() && isAlive)
			if (t < time)
			{
				for (int i = 0; i < MAX_BULLETS; i++)
				{
					if (!bullets[i]->Active())
					{
						bullets[i]->Fire(firepoint);
						time = 0;
						break;
					}
				}
				//time = 0;
			}
		if (firePointEntity)
			firepoint = firePointEntity->Pos();

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (bullets[i]->Active())
			{
				if (player->Pos().x > Pos().x)
				{
					bullets[i]->Translate((player->Pos().Normalized()) * 5);
				}
				else
				{
					bullets[i]->Translate((Vector2((player->Pos().x * -1), player->Pos().y)).Normalized() * 5);
				}

				if (Pos().y < -bullets[i]->OFFSCREEN_BUFFER || Pos().y > Graphics::screenHeight + bullets[i]->OFFSCREEN_BUFFER || Pos().x < -bullets[i]->OFFSCREEN_BUFFER || Pos().x > Graphics::screenWidth + bullets[i]->OFFSCREEN_BUFFER)
				{
					bullets[i]->Reload();
				}
			}
		}
		AimTowardsPlayer(player);
	}
	
}

