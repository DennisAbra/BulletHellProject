#pragma warning(push)
#pragma warning(disable : 26812)
#include "Enemy.h"

std::vector<std::vector<Vector2>> Enemy::paths;

void Enemy::CreatePaths()
{
	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({ Vector2(Graphics::screenWidth * 0, Graphics::screenHeight * 0), Vector2(Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.05f),
		Vector2(Graphics::screenWidth * 0.3f,  Graphics::screenHeight * 0.25f),Vector2(Graphics::screenWidth * 0.6f, Graphics::screenHeight * 0.7f) }, 180);

	path->AddCurve({ Vector2(Graphics::screenWidth * 0.7f, Graphics::screenHeight * 0.2f), Vector2(Graphics::screenWidth * 0.05f, Graphics::screenHeight * 0.5f),
		Vector2(Graphics::screenWidth * 0.8f, Graphics::screenHeight * 0.3f),Vector2(Graphics::screenWidth * 1.1f, Graphics::screenHeight * 0.5f) }, 180);

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
	if((paths[currentPath][currentWaypoint] - Pos()).MagnitudeSqr() < epsilon)
	{
		currentWaypoint++;
	}

	if (currentWaypoint < paths[currentPath].size())
	{
		Vector2 distance = paths[currentPath][currentWaypoint] - Pos();
		Translate(distance.Normalized() * timer->DeltaTime() * speed);

		Rotation(atan2(distance.y, distance.x) * radToDeg + 180.0f);
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
#pragma warning(pop)