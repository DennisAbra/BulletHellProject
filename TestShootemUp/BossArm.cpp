#include "BossArm.h"
#include "BoxCollider.h"
#include "PhysManager.h"


BossArm::BossArm(int path, std::string textureName, Player* player) : Enemy(path, textureName, NULL)
{

}

BossArm::BossArm(int path, std::string textureName, InputManager* input, Player* player) : Enemy(path, textureName, player), input(input)
{
	speed = 0.f;
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

	//id = PhysManager::Instance()->RegisterEntity(this, PhysManager::CollisionLayers::Hostile);
}

BossArm::~BossArm()
{

	player = nullptr;

	input = nullptr;


}


Vector2 BossArm::FindFirePoint(Vector2 offset, float angle)
{
	angle = (angle)* degToRad;
	Vector2 newVector = offset - player->Pos();
	//float rotatedX = cos(angle) * (offset.x - newVector.x) - sin(angle) * (offset.y - newVector.y) + newVector.x;
	//float rotatedY = cos(angle) * (offset.x - newVector.x) - sin(angle) * (offset.y - newVector.y) + newVector.y;


	return newVector + player->Pos() + Parent()->Rotation() /*{ rotatedX, rotatedY }*/;
}

void BossArm::AimTowardsPlayer(Player* player)
{
	this->player = player;
	distanceToPlayer = this->Pos() - player->Pos();
	Rotation(atan2(distanceToPlayer.y, distanceToPlayer.x) * radToDeg + 90.f);
}


void BossArm::Update()
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
			//printf("X: %f, Y: %f\n", Pos().x, Pos().y);
			
			//HandleFiring();
			for (int i = 0; i < MAX_BULLETS; i++)
			{
				if (!bullets[i]->Active())
				{
					bullets[i]->Fire(firepoint);
					printf("FIRE");
					time = 0;
						break;
				}
			}
			//time = 0;
		}

	firepoint = FindFirePoint({ Pos().x + 50, Pos().y + 100 }, Rotation());
	//TODO Fix this

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i]->Active())
		{
			//Check if it's a BossBullet and do this inside Bullet->Update()
			bullets[i]->Translate( (player->Pos().Normalized()) * 5); // This should be distance between player and boss // I think
			if (Pos().y < -bullets[i]->OFFSCREEN_BUFFER || Pos().y > Graphics::screenHeight + bullets[i]->OFFSCREEN_BUFFER || Pos().x < -bullets[i]->OFFSCREEN_BUFFER || Pos().x > Graphics::screenWidth + bullets[i]->OFFSCREEN_BUFFER)
			{
				bullets[i]->Reload();
			}
		}


		//bullets[i]->Update();
	}
	AimTowardsPlayer(player);
}

