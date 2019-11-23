#include "BossArm.h"
#include "BoxCollider.h"
#include "PhysManager.h"

BossArm::BossArm(int path, std::string textureName) : Enemy(path, textureName) 
{
	
}

BossArm::BossArm(int path, std::string textureName, InputManager* input) : Enemy(path,textureName), input(input)
{
	speed = 0.f;
	posOffset = Vector2(110, 50);
	AddCollider(new BoxCollider(texture->ScaledDimensions() * 0.5f,&point));
	
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


	speed = 50.0f;
	id = PhysManager::Instance()->RegisterEntity(this, PhysManager::CollisionLayers::Hostile);
}

BossArm::~BossArm()
{

	player = nullptr;

	input = nullptr;


}


void BossArm::AimTowardsPlayer(Player* player)
{
	this->player = player;
	distanceToPlayer = this->Pos() - player->Pos();
	Rotation(atan2(distanceToPlayer.y, distanceToPlayer.x) * radToDeg + 90.f);		
}

void BossArm::MoveOffset()
{
	
	if (input->KeyDown(SDL_SCANCODE_UP))
	{
		rotation++;
	}

	if (input->KeyDown(SDL_SCANCODE_DOWN))
	{
		rotation--;
	}
	
}




void BossArm::Update()
{	
		MoveOffset();
		if (invincible)
		{
			Invincible();
		}

		if (health <= 0)
		{
			isAlive = false; //TODO Change this to a bool - isAlive
		}
		
		AimTowardsPlayer(player);
}

