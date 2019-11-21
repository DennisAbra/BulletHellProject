#pragma warning(push)
#pragma warning(disable : 26812)
#include "Enemy.h"
#include "BoxCollider.h"
#include "PhysManager.h"


std::vector<std::vector<Vector2>> Enemy::paths;

bool Enemy::IgnoreCollisions()
{
	return active == false;
}

void Enemy::CreatePaths()
{
	//int currentPath = 0;

	for (int currentPath = 0; currentPath < 3; currentPath++)
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
		}


		//path->AddCurve({ Vector2(Graphics::screenWidth * 0.7f, Graphics::screenHeight * 0.2f), Vector2(Graphics::screenWidth * 0.05f, Graphics::screenHeight * 0.5f),
			//Vector2(Graphics::screenWidth * 0.8f, Graphics::screenHeight * 0.3f),Vector2(Graphics::screenWidth * 1.1f, Graphics::screenHeight * 0.5f) }, 180);

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

	speed = 50.0f;
}

Enemy::~Enemy()
{
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

		Rotation(atan2(distance.y, distance.x) * radToDeg);
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

		}
	}



//TODO create a timer. 
// When timer reaches x amount of accumulated time
//Switch to Reset fly in state
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


void Enemy::Update()
{
	HandleStates();
}

void Enemy::Render()
{
	if (Active())
	{
		texture->Render();

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