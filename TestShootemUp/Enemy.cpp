#pragma warning(push)
#pragma warning(disable : 26812)
#include "Enemy.h"
#include "BoxCollider.h"
#include "PhysManager.h"


std::vector<std::vector<Vector2>> Enemy::paths;

void Enemy::CreatePaths()
{
	for (int currentPath = 0; currentPath < 4; currentPath++)
	{
		BezierPath* path = new BezierPath();

		switch (currentPath)
		{
		case 0:
			path->AddCurve(path->TopLeftSCurve(), 45);
			break;
		case 1:
			path->AddCurve(path->TopRightSCurve(), 45);
			break;
		case 2:
			path->AddCurve(path->TopUCurve(), 45);
			break;
		case 3:
			path->AddCurve(path->DeadCenter(), 1);
			break;
		}

		paths.push_back(std::vector<Vector2>());
		path->Sample(&paths[currentPath]);

		delete path;
		path = nullptr;
	}

}

Enemy::Enemy(int path)
{
	timer = Timer::Instance();

	currentPath = path;

	currentState = flyIn;

	currentWaypoint = 0;
	Pos(paths[currentPath][currentWaypoint]);

	texture = new Texture("DuckKing.png");
	texture->Parent(this);

	texture->Pos(Vec2_Zero);

	speed = 100.0f;


	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i] = new Bullet(false, "CocaCola.png");
	}

	AddCollider(new BoxCollider(Vector2(50, 50)));
	id = PhysManager::Instance()->RegisterEntity(this, PhysManager::CollisionLayers::Hostile);
}

Enemy::Enemy(int path, std::string textureName)
{
	timer = Timer::Instance();

	currentPath = path;

	currentState = flyIn;

	currentWaypoint = 0;
	Pos(paths[currentPath][currentWaypoint]);

	texture = new Texture(textureName);
	texture->Parent(this);

	texture->Pos(Vec2_Zero);


	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i] = new Bullet(false, "CocaCola.png");
	}

	speed = 50.0f;
}

Enemy::~Enemy()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete bullets[i];
		bullets[i] = nullptr;
	}

	timer = nullptr;

	delete texture;
	texture = nullptr;
}

void Enemy::HandleFlyInState()
{
	if ((paths[currentPath][currentWaypoint] - Pos()).MagnitudeSqr() < epsilon)
	{
		currentWaypoint++;
	}

	if (currentWaypoint < paths[currentPath].size())
	{
		Vector2 distance = paths[currentPath][currentWaypoint] - Pos();
		Translate(distance.Normalized() * timer->DeltaTime() * speed);

		//Rotation(atan2(distance.y, distance.x) * radToDeg);
	}
	else
	{
		currentState = inactive;
	}
}

void Enemy::HandleInactiveState()
{
	Active(false);

	if (!ObjectPooling::Instance()->enemies[4]->active)
	{
		for (int i = 0; i < 5; i++)
		{
			ObjectPooling::Instance()->enemies[i]->Active(true);
			ObjectPooling::Instance()->enemies[i]->Pos(ObjectPooling::Instance()->enemies[i]->startPos);
			ObjectPooling::Instance()->enemies[i]->currentWaypoint = 0;
			ObjectPooling::Instance()->enemies[i]->currentState = flyIn;
			if (ObjectPooling::Instance()->enemies[i]->isAlive == false)
			{
				ObjectPooling::Instance()->enemies[i]->isAlive = true;
				ObjectPooling::Instance()->enemies[i]->health = maxHealth;
			}
		}
	}

	if (!ObjectPooling::Instance()->enemies[9]->active)
	{
		for (int i = 5; i < 10; i++)
		{
			ObjectPooling::Instance()->enemies[i]->Active(true);
			ObjectPooling::Instance()->enemies[i]->Pos(ObjectPooling::Instance()->enemies[i]->startPos);
			ObjectPooling::Instance()->enemies[i]->currentWaypoint = 0;
			ObjectPooling::Instance()->enemies[i]->currentState = flyIn;

			if (ObjectPooling::Instance()->enemies[i]->isAlive == false)
			{
				ObjectPooling::Instance()->enemies[i]->isAlive = true;
				ObjectPooling::Instance()->enemies[i]->health = maxHealth;
			}
		}
	}

	if (!ObjectPooling::Instance()->enemies[14]->active)
	{
		for (int i = 10; i < 15; i++)
		{
			ObjectPooling::Instance()->enemies[i]->Active(true);
			ObjectPooling::Instance()->enemies[i]->Pos(ObjectPooling::Instance()->enemies[i]->startPos);
			ObjectPooling::Instance()->enemies[i]->currentWaypoint = 0;
			ObjectPooling::Instance()->enemies[i]->currentState = flyIn;

			if (ObjectPooling::Instance()->enemies[i]->isAlive == false)
			{
				ObjectPooling::Instance()->enemies[i]->isAlive = true;
				ObjectPooling::Instance()->enemies[i]->health = maxHealth;
			}
		}
	}
}


void Enemy::HandleDeadState()
{

}



void Enemy::HandleStates()
{
	switch (currentState)
	{
	case flyIn:
		HandleFlyInState();
		break;
	case inactive:
		HandleInactiveState();
		break;
	case dead:
		HandleDeadState();
		break;

	}
}

void Enemy::HandleFiring()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (!bullets[i]->Active())
		{
			bullets[i]->Fire(firepoint);
		}
	}

}

void Enemy::Hit(PhysEntity* other)
{
	if (!invincible)
	{
		invincible = true;
		health--;
		wasHit = true;
	}
}

void Enemy::Invincible()
{
	invincibilityFrameTimer -= timer->DeltaTime();
	if (invincibilityFrameTimer <= 0.0f)
	{
		invincible = false;
		if (!invincible)
		{
			invincibilityFrameTimer = maxInvincibilityFrameTimer;
		}
	}

}

bool Enemy::IgnoreCollisions()
{
	if (isAlive)
	{
		return invincible;
	}
	if (wasHit && isAlive)
	{
		return wasHit;
	}
	else
	{
		return !isAlive;
	}
}

bool Enemy::WasHit()
{
	return wasHit;
}


void Enemy::Update()
{
	HandleStates();
	firepoint = Pos();

	static float time;
	static float t = 2.0f;
	time += timer->DeltaTime();
	if (t < time)
	{
		HandleFiring();
		time = 0;
	}

	if (wasHit)
	{
		wasHit = false;
	}

	if (invincible)
	{
		Invincible();
	}

	if (health <= 0)
	{
		isAlive = false; //TODO Change this to a bool - isAlive
	}

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i]->Update();
	}
}

void Enemy::Render()
{
	if (Active() && isAlive)
	{
		texture->Render();

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			bullets[i]->Render();
		}

		if (DEBUG_LINES)
		{
			for (int i = 0; i < paths[currentPath].size() - 1; i++)
			{
				Graphics::Instance()->DrawLine(paths[currentPath][i].x, paths[currentPath][i].y, paths[currentPath][i + 1].x, paths[currentPath][i + 1].y);
			}
		}

		PhysEntity::Render();
	}
}
#pragma warning(pop)