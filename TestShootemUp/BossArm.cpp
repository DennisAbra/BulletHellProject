#include "BossArm.h"
#include "BoxCollider.h"
#include "PhysManager.h"


BossArm::BossArm(int path, std::string textureName) : Enemy(path, textureName)
{

}

BossArm::BossArm(int path, std::string textureName, InputManager* input) : Enemy(path, textureName), input(input)
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
	float rotatedX = cos(angle) * (offset.x - Pos().x) - sin(angle) * (offset.y - Pos().y) + Pos().x;
	float rotatedY = cos(angle) * (offset.x - Pos().x) - sin(angle) * (offset.y - Pos().y) + Pos().y;

	return { rotatedX, rotatedY };
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
			HandleFiring();
			time = 0;
		}

	firepoint = FindFirePoint({ Pos().x + 50, Pos().y + 150 }, Rotation());
	//TODO Fix this
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i]->Active())
		{
			//Check if it's a BossBullet and do this inside Bullet->Update()
			bullets[i]->Translate(player->Pos().Normalized() * 5);
		}
		bullets[i]->Update();
	}
	AimTowardsPlayer(player);
}

