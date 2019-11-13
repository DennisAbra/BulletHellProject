#include "Enemy.h"

std::vector<std::vector<Vector2>> Enemy::paths;

void Enemy::CreatePaths()
{
	int currentPath = 0;
	BezierPath* path = new BezierPath();
	path->AddCurve({ Vector2(0.0f, 0.0f), Vector2(500.0f, 50.0f),Vector2(345.0f, 310.0f),Vector2(800.0f, 650.0f) }, 90);

	paths.push_back(std::vector<Vector2>());
	path->Sample(&paths[currentPath]);
	delete path;
	path = nullptr;
}

Enemy::Enemy(int path)
{
	timer = Timer::Instance();

	currentPath = path;

	currentState = flyIn;

	currentWaypoint = 0;
	Pos(paths[currentPath][currentWaypoint]);

	texture = new Texture("swordfish.png");
	texture->Parent(this);
	texture->Pos(Vec2_Zero);

	speed = 100.0f;
}

Enemy::~Enemy()
{
	timer = nullptr;

	delete texture;
	texture = nullptr;
}

void Enemy::HandleFlyInState()
{
	if((paths[currentPath][currentWaypoint] - Pos()).MagnitudeSqr() < epsilon)
	{
		currentWaypoint++;
	}

	if (currentWaypoint < paths[currentPath].size())
	{
		Vector2 distance = paths[currentPath][currentWaypoint] - Pos();
		Translate(distance.Normalized() * timer->DeltaTime() * speed);
	}
	else
	{
		currentState = formation;
	}
}

void Enemy::HandleFormationState()
{

}

void Enemy::HandleDiveState()
{

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
	case formation:
		HandleFormationState();
		break;
	case dive:
		HandleDiveState();
		break;
	case dead:
		HandleDeadState();
		break;

	}
}

void Enemy::Update()
{
	if (Active())
	{
		HandleStates();
	}
}

void Enemy::Render()
{
	if (Active())
	{
		texture->Render();

		for (int i = 0; i < paths[currentPath].size() - 1; i++)
		{
			Graphics::Instance()->DrawLine(paths[currentPath][i].x, paths[currentPath][i].y, paths[currentPath][i + 1].x, paths[currentPath][i + 1].y);
		}
	}
}
